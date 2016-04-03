/*
** Socket.hh for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue May 26 20:40:53 2015 Alexis Bertholom
** Last update Wed Jul  8 21:10:24 2015 Alexis Bertholom
*/

#pragma once

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include "StdError.hh"

class		Socket
{
public:
  enum			Domain
    {
      Unix =		AF_UNIX,
      Local =		AF_LOCAL,
      Inet =		AF_INET,
      Inet6 =		AF_INET6,
      IPX =		AF_IPX,
      NetLink =		AF_NETLINK,
      AX25 =		AF_AX25,
      AppleTalk =	AF_APPLETALK,
      Packet =		AF_PACKET
    };

  enum			Type
    {
      Stream =		SOCK_STREAM,
      Datagram =	SOCK_DGRAM,
      SeqPacket =	SOCK_SEQPACKET,
      Raw =		SOCK_RAW,
      Rdm =		SOCK_RDM
    };

  enum			Protocol
    {
      Any =		0,
      Tcp =		6,
      Udp =		17
    };

public:
  Socket(int fd, bool closeFd = true);
  Socket(Type type, Domain domain = Socket::Inet, Protocol protocol = Socket::Any);
  Socket(Socket const&) = delete;
  Socket(Socket&& sock);
  ~Socket();

  Socket&	operator=(Socket const&) = delete;

public:
  void		reset(int fd, bool closeFd = true);
  void		reset(Type type, Domain domain = Socket::Inet, Protocol protocol = Socket::Any);

public:
  int		fd() const;
  bool		isNonBlocking() const;
  void		setNonBlock(bool set);

public:
  size_t	write(std::string const& string);
  size_t	write(void const* buf, size_t size);
  size_t	read(void* buf, size_t size);

public:
  void		connect(struct sockaddr const& addr, socklen_t addrlen);
  void		bind(struct sockaddr const& addr, socklen_t addrlen);
  void		listen(int backlog);
  int		accept(struct sockaddr* addr, socklen_t* addrlen);

public:
  void		keepAlive(bool enable);
  void		setopt(int optname, int value);
  void		setopt(Protocol level, int optname, int value);
  void		setopt(Protocol level, int optname, void const* optval, socklen_t optlen);

public:
  int		getError();
  void		getopt(Protocol level, int optname, void* optval, socklen_t* optlen);

public:
  void		setopt(int level, int optname, void const* optval, socklen_t optlen);
  void		getopt(int level, int optname, void* optval, socklen_t* optlen);

public:
  static int	create(Type type, Domain domain = Socket::Inet, Protocol protocol = Socket::Any);

private:
  int		getFlags() const;
  void		setFlags(int flags);

private:
  int		_fd;
  int		_flags;
  bool		_close;
};

inline void	Socket::reset(Type type, Domain domain, Protocol protocol)
{
  this->reset(Socket::create(type, domain, protocol), true);
}

inline int	Socket::fd() const
{
  return (this->_fd);
}

inline bool	Socket::isNonBlocking() const
{
  return (this->_flags & O_NONBLOCK);
}

inline void	Socket::setNonBlock(bool set)
{
  if (set != this->isNonBlocking())
    this->setFlags(set ? (this->_flags | O_NONBLOCK) : (this->_flags & (~O_NONBLOCK)));
}

/*
** syscalls:
*/

inline size_t	Socket::write(std::string const& string)
{
  return (this->write(string.c_str(), string.size()));
}

inline size_t	Socket::write(void const* buf, size_t size)
{
  ssize_t	ret(::write(this->_fd, buf, size));

  if (ret == -1)
    throw (StdError("write"));
  return (ret);
}

inline size_t	Socket::read(void* buf, size_t size)
{
  ssize_t	ret(::read(this->_fd, buf, size));

  if (ret == -1)
    throw (StdError("read"));
  return (ret);
}

inline void	Socket::connect(struct sockaddr const& addr, socklen_t addrlen)
{
  if (::connect(this->_fd, &addr, addrlen) == -1)
    throw (StdError("connect"));
}

inline void	Socket::bind(struct sockaddr const& addr, socklen_t addrlen)
{
  if (::bind(this->_fd, &addr, addrlen) == -1)
    throw (StdError("bind"));
}

inline void	Socket::listen(int backlog)
{
  if (::listen(this->_fd, backlog) == -1)
    throw (StdError("listen"));
}

inline int	Socket::accept(struct sockaddr* addr, socklen_t* addrlen)
{
  int		ret(::accept(this->_fd, addr, addrlen));

  if (ret == -1)
    throw (StdError("accept"));
  return (ret);
}

/*
** setopt:
*/

inline void	Socket::keepAlive(bool enable)
{
  this->setopt(SO_KEEPALIVE, enable ? 1 : 0);
}

inline void	Socket::setopt(int optname, int value)
{
  this->setopt(SOL_SOCKET, optname, &value, sizeof(value));
}

inline void	Socket::setopt(Protocol level, int optname, int value)
{
  this->setopt(static_cast<int>(level), optname, &value, sizeof(value));
}

inline void	Socket::setopt(Protocol level, int optname, void const* optval, socklen_t optlen)
{
  this->setopt(static_cast<int>(level), optname, optval, optlen);
}

/*
** getopt:
*/

inline int	Socket::getError()
{
  int		err;
  socklen_t	size(sizeof(err));

  this->getopt(SOL_SOCKET, SO_ERROR, &err, &size);
  return (err);
}

inline void	Socket::getopt(Protocol level, int optname, void* optval, socklen_t* optlen)
{
  this->getopt(static_cast<int>(level), optname, optval, optlen);
}

/*
** Low level:
*/

inline void	Socket::setopt(int level, int optname, void const* optval, socklen_t optlen)
{
  if (setsockopt(this->_fd, level, optname, optval, optlen) == -1)
    throw (StdError("setsockopt"));
}

inline void	Socket::getopt(int level, int optname, void* optval, socklen_t* optlen)
{
  if (getsockopt(this->_fd, level, optname, optval, optlen) == -1)
    throw (StdError("getsockopt"));
}

/*
** static:
*/

inline int	Socket::create(Type type, Domain domain, Protocol protocol)
{
  int		fd(socket(domain, type, protocol));

  if (fd == -1)
    throw (StdError("socket"));
  return (fd);
}

/*
** private:
*/

inline int	Socket::getFlags() const
{
  int		flags(fcntl(this->_fd, F_GETFL, NULL));

  if (flags == -1)
    throw (StdError("fcntl(F_GETFL)"));
  return (flags);
}

inline void	Socket::setFlags(int flags)
{
  if (fcntl(this->_fd, F_SETFL, flags) == -1)
    throw (StdError("fcntl(F_SETFL)"));
  this->_flags = flags;
}
