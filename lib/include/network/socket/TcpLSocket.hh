/*
** TcpLSocket.hh for libptr
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Jul  3 16:01:47 2015 Alexis Bertholom
** Last update Mon Jul  6 20:49:08 2015 Alexis Bertholom
*/

#pragma once

#include "TcpSocket.hh"
#include "Host.hh"
#include "StdError.hh"
#include "LogicError.hh"

class		TcpLSocket : protected Socket
{
public:
  TcpLSocket(Domain domain = Socket::Inet);
  ~TcpLSocket();

public:
  using		Socket::fd;

public:
  void		bind(int port);
  void		bind(Host const& host);
  void		bind(in_addr_t addr, int port);
  void		bind(in_addr_t addr, uint16_t port);
  void		bind(struct in_addr addr, uint16_t port);
  void		bind(struct sockaddr_in& s_in);

public:
  void		listen(int backlog = 128);
  TcpSocket	accept();
  TcpSocket	accept(struct sockaddr* addr, socklen_t* addrlen);

private:
  Domain	_domain;
  bool		_bound;
  bool		_listening;
};

inline void	TcpLSocket::bind(int port)
{
  this->bind(INADDR_ANY, port);
}

inline void	TcpLSocket::bind(Host const& host)
{
  this->bind(host.getAddrN(), host.getPortN());
}

inline void	TcpLSocket::bind(in_addr_t addr, int port)
{
  this->bind(addr, htons(port));
}

inline void	TcpLSocket::bind(struct sockaddr_in& s_in)
{
  this->Socket::bind(*reinterpret_cast<struct sockaddr*>(&s_in), sizeof(s_in));
  this->_bound = true;
}

inline void	TcpLSocket::listen(int backlog)
{
  if (!(this->_bound))
    throw (LogicError());
  this->Socket::listen(backlog);
  this->_listening = true;
}

inline TcpSocket TcpLSocket::accept()
{
  return (TcpSocket(this->Socket::accept(NULL, NULL)));
}

inline TcpSocket TcpLSocket::accept(struct sockaddr* addr, socklen_t* addrlen)
{
  return (TcpSocket(this->Socket::accept(addr, addrlen)));
}
