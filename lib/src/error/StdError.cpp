/*
** StdError.cpp for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue May 26 21:50:23 2015 Alexis Bertholom
** Last update Wed Jul  1 21:23:08 2015 Alexis Bertholom
*/

#include <cerrno>
#include <cstring>
#include "StdError.hh"

StdError::StdError()
  : std::runtime_error(strerror(errno)), _code(errno)
{
}

StdError::StdError(std::string const& error)
  : std::runtime_error(error + ": " + strerror(errno)), _code(errno)
{
}
