/*
** HostResolvError.hh for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Wed May 27 23:43:49 2015 Alexis Bertholom
** Last update Wed Jul  1 22:27:26 2015 Alexis Bertholom
*/

#pragma once

#include <stdexcept>
#include <string>

class		HostResolvError : public std::runtime_error
{
public:
  HostResolvError();
  virtual ~HostResolvError() throw() {}

public:
  bool		critical() const;

public:
  static char const* getMessage();

private:
  bool		_critical;
};

inline bool	HostResolvError::critical() const
{
  return (this->_critical);
}
