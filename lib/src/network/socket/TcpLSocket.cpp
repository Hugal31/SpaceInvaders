/*
** TcpLSocket.cpp for libptr
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Jul  3 16:34:54 2015 Alexis Bertholom
** Last update Fri Jul  3 23:17:59 2015 Alexis Bertholom
*/

#include "TcpLSocket.hh"

TcpLSocket::TcpLSocket(Domain domain)
  : Socket(Socket::Stream, domain),
    _domain(domain),
    _bound(false)
{
  this->setopt(SO_REUSEADDR, 1);
}

TcpLSocket::~TcpLSocket()
{
}

void		TcpLSocket::bind(in_addr_t addr, uint16_t port)
{
  struct sockaddr_in s_in;

  s_in.sin_family = static_cast<int>(_domain);
  s_in.sin_port = port;
  s_in.sin_addr.s_addr = addr;
  this->bind(s_in);
}

void		TcpLSocket::bind(struct in_addr addr, uint16_t port)
{
  struct sockaddr_in s_in;

  s_in.sin_family = static_cast<int>(this->_domain);
  s_in.sin_port = port;
  s_in.sin_addr = addr;
  this->bind(s_in);
}
