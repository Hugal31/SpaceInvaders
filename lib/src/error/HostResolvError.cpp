/*
** HostResolvError.cpp for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Wed May 27 23:50:02 2015 Alexis Bertholom
** Last update Wed Jul  1 21:21:53 2015 Alexis Bertholom
*/

#include <netdb.h>
#include "HostResolvError.hh"

HostResolvError::HostResolvError()
  : std::runtime_error(this->getMessage()),
    _critical(h_errno != TRY_AGAIN)
{
}

char const*	HostResolvError::getMessage()
{
  char const*	err(hstrerror(h_errno));

  return (err ? err : "Unknown hostname resolution error");
}
