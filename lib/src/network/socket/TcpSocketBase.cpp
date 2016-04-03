/*
** TcpSocketBase.cpp for libptr
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Jul  3 22:28:33 2015 Alexis Bertholom
** Last update Wed Jul  8 21:09:03 2015 Alexis Bertholom
*/

#include <netinet/tcp.h>
#include "TcpSocketBase.hh"

TcpSocketBase::TcpSocketBase(int fd, bool close)
  : Socket(fd, close),
    _disconnected(false)
{
}

TcpSocketBase::TcpSocketBase(Domain domain)
  : Socket(Socket::Stream, domain),
    _disconnected(false)
{
}

TcpSocketBase::TcpSocketBase(TcpSocketBase&& sock)
  : Socket(std::move(sock)),
    _disconnected(false)
{
  sock._disconnected = true;
}

void		TcpSocketBase::setKeepAlive(int idleTime, int probesInterval, int probesCount)
{
  this->keepAlive(true);
  this->setopt(Socket::Tcp, TCP_KEEPIDLE, idleTime);
  this->setopt(Socket::Tcp, TCP_KEEPINTVL, probesInterval);
  this->setopt(Socket::Tcp, TCP_KEEPCNT, probesCount);
}
