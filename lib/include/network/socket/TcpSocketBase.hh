/*
** TcpSocketBase.hh for libptr
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Jul  3 22:13:31 2015 Alexis Bertholom
** Last update Sat Jul  4 16:32:45 2015 Alexis Bertholom
*/

#pragma once

#include "Socket.hh"

class		TcpSocketBase : protected Socket
{
public:
  TcpSocketBase(int fd, bool close = true);
  TcpSocketBase(Domain domain = Socket::Inet);
  TcpSocketBase(TcpSocketBase const&) = delete;
  TcpSocketBase(TcpSocketBase&& sock);
  virtual ~TcpSocketBase() {}

  TcpSocketBase& operator=(TcpSocketBase const&) = delete;

public:
  using		Socket::fd;
  using		Socket::read;
  using		Socket::isNonBlocking;
  using		Socket::setNonBlock;

public:
  virtual bool	disconnected() const = 0;

public:
  void		setKeepAlive(int idleTime, int probesInterval, int probesCount);

public:
  size_t	write(std::string const& string);
  size_t	write(void const* buf, size_t size);

protected:
  void		reset(int fd, bool close = true);
  void		reset(Domain domain = Socket::Inet);

protected:
  bool		_disconnected;
};

inline size_t	TcpSocketBase::write(std::string const& string)
{
  return (this->TcpSocketBase::write(string.c_str(), string.size()));
}

inline size_t	TcpSocketBase::write(void const* buf, size_t size)
{
  try
    {
      return (this->Socket::write(buf, size));
    }
  catch (StdError const& e)
    {
      if (e.getErrorCode() != EAGAIN &&
	  e.getErrorCode() != EWOULDBLOCK &&
	  e.getErrorCode() != EFAULT &&
	  e.getErrorCode() != EINTR)
	this->_disconnected = true;
      throw;
    }
}

inline void	TcpSocketBase::reset(int fd, bool close)
{
  this->Socket::reset(fd, close);
  this->_disconnected = false;
}

inline void	TcpSocketBase::reset(Domain domain)
{
  this->Socket::reset(domain);
  this->_disconnected = false;
}
