/*
** Host.cpp for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue May 26 21:02:33 2015 Alexis Bertholom
** Last update Fri Jul  3 16:46:34 2015 Alexis Bertholom
*/

#include <algorithm>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "HostResolvError.hh"
#include "Host.hh"

Host::Host(in_addr_t addr, int port, std::ostream* logger)
  : _logger(logger),
    _hostname(),
    _addr(),
    _port(port),
    _portN(htons(port)),
    _resolved(true)
{
  this->_addrN.s_addr = addr;
  this->_addr = inet_ntoa(this->_addrN);
  this->_hostname = this->_addr;
}

Host::Host(std::string const& hostname, int port, std::ostream* logger)
  : _logger(logger),
    _hostname(hostname),
    _port(port),
    _portN(htons(port)),
    _resolved(false)
{
  this->_addrN.s_addr = inet_addr(hostname.c_str());
  if (this->_addrN.s_addr != static_cast<in_addr_t>(-1))
    {
      this->_addr = inet_ntoa(this->_addrN);
      this->_resolved = true;
    }
}

std::string const& Host::getAddr() const
{
  if (!(this->_resolved))
    throw (std::logic_error(this->_hostname + ": unresolved hostname"));
  return (this->_addr);
}

struct in_addr	Host::getAddrN() const
{
  if (!(this->_resolved))
    throw (std::logic_error(this->_hostname + ": unresolved hostname"));
  return (this->_addrN);
}

void		Host::resolveHostname()
{
  if (this->_resolved)
    return ;
  if (this->_logger)
    {
      *(this->_logger) << "Resolving hostname " << this->_hostname;
      this->_logger->flush();
    }
  this->_resolveHostname();
  this->_resolved = true;
}

void		Host::_resolveHostname()
{
  struct hostent* he(gethostbyname(this->_hostname.c_str()));
  void*		firstAddr;

  if (he && (firstAddr = *(he->h_addr_list)))
    {
      size_t addrLength(std::max(static_cast<size_t>(he->h_length), sizeof(this->_addrN)));

      memcpy(&(this->_addrN.s_addr), firstAddr, addrLength);
      this->_addr = inet_ntoa(this->_addrN);
      if (this->_logger)
	*(this->_logger) << ": " << this->_addr << std::endl;
    }
  else
    {
      if (this->_logger)
	*(this->_logger) << ": failed !" << std::endl;
      throw (HostResolvError());
    }
}
