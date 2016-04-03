/*
** TronClient.hh for libtron
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Wed Jul  1 20:34:43 2015 Alexis Bertholom
** Last update Wed Jul  8 21:00:36 2015 Alexis Bertholom
*/

#pragma once

#include <deque>
#include <string>
#include "TronPacket.hh"
#include "TronCSocket.hh"

class		TronClient
{
public:
  TronClient() {}
  ~TronClient() {}

public:
  void		connect(Host& host, std::string const& name);
  void		move(TronPacket::Direction dir);
  void		disconnect();
  void		update();

public:
  bool		getPlayerPos(size_t pos[], Uint& id);
  bool		getPlayerEvent(TronPacket::Type& type, Uint& id);
  bool		getGameEvent(TronPacket::Type& type);
  bool		getString(std::string& string);

public:
  bool		connected() const;

private:
  TronCSocket	_sock;
  std::deque<TronPacket::PlayerEvent> _pEvents;
  std::deque<TronPacket::PlayerPos> _pPos;
  std::deque<TronPacket::Type> _gEvents;
  std::deque<std::string> _strings;
};

inline bool	TronClient::connected() const
{
  return (this->_sock.connected());
}
