/*
** TronCSocket.hh for GameOfTron
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Wed Jul  1 23:18:47 2015 Alexis Bertholom
** Last update Wed Jul  8 21:11:58 2015 Alexis Bertholom
*/

#pragma once

#include "TcpCSocket.hh"
#include "TronSocketBase.hh"

class		TronCSocket : public TronSocketBase
{
public:
  TronCSocket(Socket::Domain domain = Socket::Inet)
    : _sock(domain) {}
  TronCSocket(TcpCSocket&& sock)
    : _sock(std::move(sock)) {}
  TronCSocket(TronCSocket const&) = delete;
  virtual ~TronCSocket() {}

  TronCSocket&	operator=(TronCSocket const&) = delete;

public:
  virtual int	fd() const;
  virtual bool	disconnected() const;

protected:
  virtual size_t write(std::string const& string);
  virtual size_t write(void const* buf, size_t size);
  virtual size_t read(void* buf, size_t size);

public:
  bool		connected() const;
  void		connect(Host const& host);
  void		connect(Host const& host, int timeout);
  void		disconnect();

private:
  TcpCSocket	_sock;
};

inline int	TronCSocket::fd() const
{
  return (this->_sock.fd());
}

inline bool	TronCSocket::disconnected() const
{
  return (this->_sock.disconnected());
}

inline bool	TronCSocket::connected() const
{
  return (!this->disconnected());
}

inline size_t	TronCSocket::write(std::string const& string)
{
  return (this->_sock.write(string));
}

inline size_t	TronCSocket::write(void const* buf, size_t size)
{
  return (this->_sock.write(buf, size));
}

inline size_t	TronCSocket::read(void* buf, size_t size)
{
  return (this->_sock.read(buf, size));
}

inline void	TronCSocket::connect(Host const& host)
{
  this->_sock.connect(host);
  this->_sock.setNonBlock(true);
}

inline void	TronCSocket::connect(Host const& host, int timeout)
{
  this->_sock.connect(host, timeout);
}

inline void	TronCSocket::disconnect()
{
  this->_sock.disconnect();
}
