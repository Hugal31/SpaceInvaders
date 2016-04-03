/*
** GenericError.cpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 12:27:15 2015 Alexis Bertholom
** Last update Wed Jul  1 20:31:21 2015 Alexis Bertholom
*/

#include "GenericError.hh"

char const*	GenericError::messages[] = {
  "Unknown error",
  "Invalid window dimensions"
};

GenericError::GenericError(GenericError::Type errcode)
  : std::runtime_error(GenericError::messages[errcode]), _errcode(errcode)
{
}

GenericError::~GenericError() throw()
{
}
