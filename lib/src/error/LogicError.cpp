/*
** LogicError.cpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 12:22:49 2015 Alexis Bertholom
** Last update Fri Jul  3 23:31:20 2015 Alexis Bertholom
*/

#include "LogicError.hh"

char const*	LogicError::messages[] = {
  "Logic error",
  "Invalid parameters",
  "Trying to listen to an unbound socket",
  "Trying to accept connections on a non-listening socket"
};

LogicError::LogicError(LogicError::Type errcode)
  : std::logic_error(LogicError::messages[errcode]), _errcode(errcode)
{
}

LogicError::~LogicError() throw()
{
}
