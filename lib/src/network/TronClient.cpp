/*
** TronClient.cpp for libtron
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Wed Jul  1 22:43:05 2015 Alexis Bertholom
** Last update Thu Jul  9 17:08:55 2015 Alexis Bertholom
*/

#include <cstring>
#include "Host.hh"
#include "TronClient.hh"

void		TronClient::connect(Host& host, std::string const& name)
{
  host.resolveHostname();
  this->_sock.connect(host);
  this->_sock.sendString(name);
}

void		TronClient::move(TronPacket::Direction dir)
{
  if (this->connected())
    {
      TronPacket	packet;

      packet.type = TronPacket::PlayerDirection;
      packet.data.dir = dir;
      this->_sock.sendPacket(packet);
    }
}

void		TronClient::disconnect()
{
  if (this->connected())
    {
      TronPacket	packet;

      packet.type = TronPacket::PlayerEvLeave;
      this->_sock.sendPacket(packet);
      this->_sock.disconnect();
      this->_pEvents.clear();
      this->_pPos.clear();
      this->_gEvents.clear();
      this->_strings.clear();
    }
}

void		TronClient::update()
{
  if (this->connected())
    {
      TronPacket	packet;

      this->_sock.flush();
      while (this->_sock.getPacket(packet))
	switch (packet.type)
	  {
	  case TronPacket::PlayerPosition:
	    this->_pPos.push_back(packet.data.pos);
	    break;

	  case TronPacket::PlayerEvDeath:
	  case TronPacket::PlayerEvLeave:
	    this->_pEvents.push_back(TronPacket::PlayerEvent({packet.type, packet.data.id}));
	    break;

	  case TronPacket::GameEvStopped:
	  case TronPacket::GameEvStarted:
	    this->_gEvents.push_back(packet.type);
	    break;

	  case TronPacket::String:
	    this->_strings.push_back(this->_sock.getLastString());
	    break;

	  default:
	    break;
	  }
    }
}

bool		TronClient::getPlayerEvent(TronPacket::Type& type, Uint& id)
{
  if (this->_pEvents.empty())
    return (false);
  type = this->_pEvents.front().type;
  id = this->_pEvents.front().id;
  this->_pEvents.pop_front();
  return (true);
}

bool		TronClient::getPlayerPos(size_t pos[], Uint& id)
{
  if (this->_pPos.empty())
    return (false);
  memcpy(pos, this->_pPos.front().pos, 2 * sizeof(size_t));
  id = this->_pPos.front().id;
  this->_pPos.pop_front();
  return (true);
}

bool		TronClient::getGameEvent(TronPacket::Type& type)
{
  if (this->_gEvents.empty())
    return (false);
  type = this->_gEvents.front();
  this->_gEvents.pop_front();
  return (true);
}

bool		TronClient::getString(std::string& string)
{
  if (this->_strings.empty())
    return (false);
  string = this->_strings.front();
  this->_strings.pop_front();
  return (true);
}
