/*
** TcpCSocket.cpp for libptr
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Jul  3 22:35:20 2015 Alexis Bertholom
** Last update Wed Jul  8 21:10:31 2015 Alexis Bertholom
*/

#include <poll.h>
#include "Host.hh"
#include "TcpCSocket.hh"

TcpCSocket::TcpCSocket(Domain domain)
  : TcpSocketBase(domain),
    _domain(domain)
{
  this->_s_in.sin_family = domain;
  this->_disconnected = true;
}

TcpCSocket::TcpCSocket(TcpCSocket&& sock)
  : TcpSocketBase(std::move(sock)),
    _domain(sock._domain)
{
  this->_s_in = sock._s_in;
  this->_disconnected = sock._disconnected;
}

void		TcpCSocket::connect(Host const& host)
{
  this->prepare(host);
  this->Socket::connect(*reinterpret_cast<struct sockaddr *>(&(this->_s_in)), sizeof(this->_s_in));
  this->_disconnected = false;
}

void		TcpCSocket::prepare(Host const& host)
{
  if (this->connected())
    this->disconnect();
  this->_s_in.sin_addr = host.getAddrN();
  this->_s_in.sin_port = host.getPortN();
}

void		TcpCSocket::connect(Host const& host, int timeout)
{
  bool		nonblock(this->isNonBlocking());

  this->prepare(host);
  this->setNonBlock(true);
  try
    {
      this->_connect(timeout);
    }
  catch (std::exception const& e)
    {
      if (!nonblock)
	try
	  {
	    this->setNonBlock(false);
	  }
	catch (std::exception const&)
	  {
	  }
      throw;
    }
  if (!nonblock)
    this->setNonBlock(false);
  this->_disconnected = false;
}

void		TcpCSocket::_connect(int timeout)
{
  try
    {
      this->Socket::connect(*reinterpret_cast<struct sockaddr *>(&(this->_s_in)), sizeof(this->_s_in));
    }
  catch (StdError const& e)
    {
      if (e.getErrorCode() != EINPROGRESS)
	throw;
      this->waitForConnection(timeout);
    }
}

void		TcpCSocket::waitForConnection(int timeout)
{
  struct pollfd	pollfd;
  int		ret;

  pollfd.fd = this->fd();
  pollfd.events = (POLLOUT);
  pollfd.revents = 0;
  if ((ret = poll(&pollfd, 1, timeout)) == -1)
    throw (StdError("TcpCSocket::connect(poll)"));
  if (ret == 0)
    {
      errno = ETIMEDOUT;
      throw (StdError());
    }
  if ((errno = this->getError()))
    throw (StdError("TcpCSocket::connect"));
}
