/*
** TronSocketBase.hh for GameOfTron
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Sat Jul  4 15:04:49 2015 Alexis Bertholom
** Last update Fri Jul 10 10:45:30 2015 Alexis Bertholom
*/

#pragma once

#include <string>
#include "TronPacket.hh"

/*
** header:	000dtttt
** payload:
**   string:	size_t: size, char[size]
**   playerEv:	iiiiiiii
**   playerPos:	iiiiiiii xxxxxxxx yyyyyyyy
**
** t: Type
** d: Direction (PlayerDirection only)
** i: PlayerId
*/

class		TronSocketBase
{
public:
  TronSocketBase() : _remainingStringSize(0) {}
  TronSocketBase(TronSocketBase const&) = delete;
  virtual ~TronSocketBase() {}

  TronSocketBase& operator=(TronSocketBase const&) = delete;

public:
  virtual int	fd() const = 0;
  virtual bool	disconnected() const = 0;

protected:
  virtual size_t write(std::string const& string) = 0;
  virtual size_t write(void const* buf, size_t size) = 0;
  virtual size_t read(void* buf, size_t size) = 0;

public:
  bool		flush();
  void		flushInput();
  bool		flushOutput();

public:
  bool		sendPacket(TronPacket const& packet);
  bool		sendPlayerPosition(size_t x, size_t y, Uint playerId);
  bool		sendPlayerDirection(TronPacket::Direction dir);
  bool		sendPlayerEv(TronPacket::Type type, Uint playerId);
  bool		sendGameEv(TronPacket::Type type);
  bool		sendString(std::string const& string);
  bool		getPacket(TronPacket& packet);
  std::string const& getLastString() const;

private:
  bool		getPlayerPosition(TronPacket& packet);
  bool		getPlayerEv(TronPacket& packet, TronPacket::Type type);
  bool		fillString(TronPacket& packet);
  bool		fillPacket(TronPacket& packet);
  bool		fillBuffer(size_t minSize);
  bool		_fillBuffer();

private:
  std::string	_inBuffer;
  std::string	_outBuffer;
  std::string	_lastString;
  size_t	_remainingStringSize;
};

inline bool	TronSocketBase::flush()
{
  this->flushInput();
  return (this->flushOutput());
}

inline void	TronSocketBase::flushInput()
{
  while (this->_fillBuffer());
}

inline std::string const& TronSocketBase::getLastString() const
{
  return (this->_lastString);
}

inline bool	TronSocketBase::sendPacket(TronPacket const& packet)
{
  switch (packet.type)
    {
    case TronPacket::PlayerPosition:
      return (this->sendPlayerPosition(packet.data.pos.pos[0],
				       packet.data.pos.pos[1],
				       packet.data.pos.id));
    case TronPacket::PlayerDirection:
      return (this->sendPlayerDirection(packet.data.dir));
    case TronPacket::PlayerEvDeath:
    case TronPacket::PlayerEvLeave:
    case TronPacket::PlayerEvJoin:
    case TronPacket::PlayerEvWin:
      return (this->sendPlayerEv(packet.type, packet.data.id));
    case TronPacket::GameEvStopped:
    case TronPacket::GameEvStarted:
      return (this->sendGameEv(packet.type));
    default:
      return (false);
    }
  return (false);
}

inline bool	TronSocketBase::sendPlayerPosition(size_t x, size_t y, Uint playerId)
{
  this->_outBuffer.push_back(static_cast<char>(TronPacket::PlayerPosition));
  this->_outBuffer.push_back(static_cast<char>(playerId));
  this->_outBuffer.push_back(static_cast<char>(x));
  this->_outBuffer.push_back(static_cast<char>(y));
  return (this->flushOutput());
}

inline bool	TronSocketBase::sendPlayerDirection(TronPacket::Direction dir)
{
  this->_outBuffer.push_back(static_cast<char>((TronPacket::PlayerDirection & 0xf) |
					       (dir == TronPacket::Left ? 0x10 : 0)));
  return (this->flushOutput());
}

inline bool	TronSocketBase::sendPlayerEv(TronPacket::Type type, Uint playerId)
{
  this->_outBuffer.push_back(static_cast<char>(type));
  this->_outBuffer.push_back(static_cast<char>(playerId));
  return (this->flushOutput());
}

inline bool	TronSocketBase::sendGameEv(TronPacket::Type type)
{
  this->_outBuffer.push_back(static_cast<char>(type));
  return (this->flushOutput());
}

inline bool	TronSocketBase::sendString(std::string const& string)
{
  size_t	size(string.size());

  this->_outBuffer.push_back(static_cast<char>(TronPacket::String));
  this->_outBuffer.append(reinterpret_cast<char const*>(&size), sizeof(size_t));
  this->_outBuffer.append(string);
  return (this->flushOutput());
}
