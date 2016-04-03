/*
** TronSocketBase.cpp for GameOfTron
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Sat Jul  4 15:23:24 2015 Alexis Bertholom
** Last update Fri Jul 10 11:01:06 2015 Alexis Bertholom
*/

#include <iostream>
#include <cstring>
#include "StdError.hh"
#include "TronPacket.hh"
#include "TronSocketBase.hh"

bool		TronSocketBase::flushOutput()
{
  if (!(this->_outBuffer.size()))
    return (false);
  try
    {
      size_t	ret(this->write(this->_outBuffer));

      if (ret)
	this->_outBuffer.erase(0, ret);
      return (this->_outBuffer.size() != 0);
    }
  catch (StdError const& e)
    {
      if (e.getErrorCode() != EAGAIN && e.getErrorCode() != EWOULDBLOCK)
	std::cerr << e.what() << std::endl;
    }
  return (false);
}

bool		TronSocketBase::getPacket(TronPacket& packet)
{
  if (this->_remainingStringSize)
    return (this->fillString(packet));
  return (this->fillPacket(packet));
}

bool		TronSocketBase::fillString(TronPacket& packet)
{
  size_t	size;

  size = ((this->_remainingStringSize > this->_inBuffer.size()) ?
	  this->_inBuffer.size() : this->_remainingStringSize);
  this->_lastString.append(this->_inBuffer, 0, size);
  this->_inBuffer.erase(0, size);
  if ((this->_remainingStringSize -= size))
    return (false);
  packet.type = TronPacket::String;
  packet.data.size = this->_lastString.size();
  return (true);
}

bool		TronSocketBase::fillPacket(TronPacket& packet)
{
  char		b0;
  TronPacket::Type type;

  if (this->_inBuffer.size() < 1)
    return (false);
  b0 = this->_inBuffer[0];
  type = static_cast<TronPacket::Type>(b0 & 0xf);
  this->_inBuffer.erase(0, 1);
  switch (type)
    {
    case TronPacket::PlayerPosition:
      return (this->getPlayerPosition(packet));
    case TronPacket::PlayerDirection:
      packet.type = TronPacket::PlayerDirection;
      packet.data.dir = ((b0 & 0x10) ? TronPacket::Left : TronPacket::Right);
      return (true);
    case TronPacket::PlayerEvDeath:
    case TronPacket::PlayerEvLeave:
    case TronPacket::PlayerEvJoin:
    case TronPacket::PlayerEvWin:
      return (this->getPlayerEv(packet, type));
    case TronPacket::GameEvStopped:
    case TronPacket::GameEvStarted:
      packet.type = type;
      return (true);
    case TronPacket::String:
      if (this->_inBuffer.size() < sizeof(size_t))
	return (false);
      this->_inBuffer.copy(reinterpret_cast<char*>(&(this->_remainingStringSize)), sizeof(size_t));
      this->_lastString.clear();
      return (this->fillString(packet));
    default:
      return (false);
    }
  return (true);
}

bool		TronSocketBase::getPlayerPosition(TronPacket& packet)
{
  if (this->_inBuffer.size() < 3)
    return (false);
  packet.type = TronPacket::PlayerPosition;
  packet.data.pos.id = this->_inBuffer[0];
  packet.data.pos.pos[0] = this->_inBuffer[1];
  packet.data.pos.pos[1] = this->_inBuffer[2];
  this->_inBuffer.erase(0, 3);
  return (true);
}

bool		TronSocketBase::getPlayerEv(TronPacket& packet, TronPacket::Type type)
{
  if (this->_inBuffer.size() < 1)
    return (false);
  packet.type = type;
  packet.data.id = this->_inBuffer[0];
  this->_inBuffer.erase(0, 1);
  return (true);
}

bool		TronSocketBase::fillBuffer(size_t minSize)
{

  if (this->_inBuffer.size() >= minSize)
    return (true);
  this->flushInput();
  return (this->_inBuffer.size() >= minSize);
}

bool		TronSocketBase::_fillBuffer()
{
  char		buf[4096];

  try
    {
      size_t	ret(this->read(buf, sizeof(buf)));

      if (ret)
	{
	  this->_inBuffer.append(buf, ret);
	  return (ret == sizeof(buf));
	}
    }
  catch (StdError const& e)
    {
      if (e.getErrorCode() != EAGAIN && e.getErrorCode() != EWOULDBLOCK)
	std::cerr << e.what() << std::endl;
    }
  return (false);
}
