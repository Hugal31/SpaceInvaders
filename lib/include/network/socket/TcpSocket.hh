/*
** TcpSocket.hpp for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue May 26 20:13:33 2015 Alexis Bertholom
** Last update Sat Jul  4 16:19:30 2015 Alexis Bertholom
*/

#pragma once

#include "TcpSocketBase.hh"

class		Host;

class		TcpSocket : public TcpSocketBase
{
public:
  TcpSocket(int fd, bool close = true)
    : TcpSocketBase(fd, close) {}
  TcpSocket(TcpSocket const&) = delete;
  TcpSocket(TcpSocket&& sock)
    : TcpSocketBase(std::move(sock)) {}
  virtual ~TcpSocket() {}

  TcpSocket&	operator=(TcpSocket const&) = delete;

public:
  virtual bool	disconnected() const;

public:
  void		reset(int fd, bool close = true);
};

inline bool	TcpSocket::disconnected() const
{
  return (this->_disconnected);
}

inline void	TcpSocket::reset(int fd, bool close)
{
  this->TcpSocketBase::reset(fd, close);
}
