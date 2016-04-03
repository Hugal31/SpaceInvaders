/*
** Socket.cpp for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue May 26 20:46:38 2015 Alexis Bertholom
** Last update Wed Jul  8 21:10:12 2015 Alexis Bertholom
*/

#include "Socket.hh"

Socket::Socket(int fd, bool close)
  : _fd(fd),
    _flags(this->getFlags()),
    _close(close)
{
}

Socket::Socket(Type type, Domain domain, Protocol protocol)
  : _fd(Socket::create(type, domain, protocol)),
    _flags(this->getFlags()),
    _close(true)
{
}

Socket::Socket(Socket&& sock)
  : _fd(sock._fd),
    _flags(sock._flags),
    _close(sock._close)
{
  sock._fd = -1;
  sock._close = false;
}

Socket::~Socket()
{
  if (this->_close)
    close(this->_fd);
}

void		Socket::reset(int fd, bool closeFd)
{
  int		oldFd(this->_fd);

  this->_fd = fd;
  this->_flags = this->getFlags();
  if (this->_close)
    close(oldFd);
  this->_close = closeFd;
}
