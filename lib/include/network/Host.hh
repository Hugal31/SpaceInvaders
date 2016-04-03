/*
** Host.hh for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue May 26 21:01:40 2015 Alexis Bertholom
** Last update Fri Jul  3 16:40:04 2015 Alexis Bertholom
*/

#pragma once

#include <iostream>
#include <string>
#include <arpa/inet.h>

class			Host
{
public:
  Host(in_addr_t addr, int port, std::ostream* logger = NULL);
  Host(std::string const& hostname, int port, std::ostream* logger = NULL);
  ~Host() {}

public:
  std::string const&	getHostname() const;
  int			getPort() const;
  uint16_t		getPortN() const;
  std::string const&	getAddr() const;
  struct in_addr	getAddrN() const;
  void			resolveHostname();

private:
  void			_resolveHostname();

private:
  std::ostream*		_logger;
  std::string		_hostname;
  std::string		_addr;
  struct in_addr	_addrN;
  int			_port;
  uint16_t		_portN;
  bool			_resolved;
};

inline std::string const& Host::getHostname() const
{
  return (this->_hostname);
}

inline int		Host::getPort() const
{
  return (this->_port);
}

inline uint16_t		Host::getPortN() const
{
  return (this->_portN);
}
