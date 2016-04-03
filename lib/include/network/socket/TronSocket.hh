/*
** TronSocket.hh for GameOfTron
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Sat Jul  4 16:13:40 2015 Alexis Bertholom
** Last update Sat Jul  4 16:45:02 2015 Alexis Bertholom
*/

#pragma once

#include "TcpSocket.hh"
#include "TronSocketBase.hh"

class		TronSocket : public TronSocketBase
{
public:
  TronSocket(int fd, bool close = true)
    : _sock(fd, close) { this->_sock.setNonBlock(true); }
  TronSocket(TcpSocket&& sock)
    : _sock(std::move(sock)) { this->_sock.setNonBlock(true); }
  TronSocket(TronSocket const&) = delete;
  virtual ~TronSocket() {}

  TronSocket&	operator=(TronSocket const&) = delete;

public:
  virtual int	fd() const;
  virtual bool	disconnected() const;

protected:
  virtual size_t write(std::string const& string);
  virtual size_t write(void const* buf, size_t size);
  virtual size_t read(void* buf, size_t size);

public:
  void		reset(int fd, bool close);

private:
  TcpSocket	_sock;
};

inline int	TronSocket::fd() const
{
  return (this->_sock.fd());
}

inline bool	TronSocket::disconnected() const
{
  return (this->_sock.disconnected());
}

inline size_t	TronSocket::write(std::string const& string)
{
  return (this->_sock.write(string));
}

inline size_t	TronSocket::write(void const* buf, size_t size)
{
  return (this->_sock.write(buf, size));
}

inline size_t	TronSocket::read(void* buf, size_t size)
{
  return (this->_sock.read(buf, size));
}

inline void	TronSocket::reset(int fd, bool close)
{
  return (this->_sock.reset(fd, close));
}
