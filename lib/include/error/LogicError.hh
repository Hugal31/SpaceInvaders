/*
** LogicError.hpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 11:59:38 2015 Alexis Bertholom
** Last update Fri Jul  3 23:29:31 2015 Alexis Bertholom
*/

#pragma once

#include <stdexcept>

class			LogicError : public std::logic_error
{
public:
  enum			Type
    {
      Unknown =	0,
      InvalidParameters,
      ListenUnboundSocket,
      AcceptNotListeningSocket
    };

public:
  LogicError(LogicError::Type errcode = Unknown);
  virtual ~LogicError() throw();

protected:
  LogicError::Type	_errcode;

private:
  static char const*	messages[];
};
