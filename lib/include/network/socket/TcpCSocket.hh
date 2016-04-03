/*
** TcpCSocket.hh for libptr
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Jul  3 21:55:57 2015 Alexis Bertholom
** Last update Sat Jul  4 16:47:27 2015 Alexis Bertholom
*/

#pragma once

#include <netinet/in.h>
#include "TcpSocketBase.hh"

class		Host;

class		TcpCSocket : public TcpSocketBase
{
public:
  TcpCSocket(Domain domain = Socket::Inet);
  TcpCSocket(TcpCSocket const&) = delete;
  TcpCSocket(TcpCSocket&& sock);
  virtual ~TcpCSocket() {}

  TcpCSocket&	operator=(TcpCSocket const&) = delete;

public:
  bool		connected() const;
  virtual bool	disconnected() const;

public:
  void		connect(Host const& host);
  void		connect(Host const& host, int timeout);
  void		disconnect();

private:
  void		prepare(Host const& host);
  void		_connect(int timeout);
  void		waitForConnection(int timeout);

private:
  Domain	_domain;
  struct sockaddr_in _s_in;
};

inline bool	TcpCSocket::connected() const
{
  return (!(this->_disconnected));
}

inline bool	TcpCSocket::disconnected() const
{
  return (this->_disconnected);
}

inline void	TcpCSocket::disconnect()
{
  this->reset(this->_domain);
  this->_disconnected = true;
}
