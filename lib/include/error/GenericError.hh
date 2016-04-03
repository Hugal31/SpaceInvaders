/*
** GenericError.hpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 11:55:06 2015 Alexis Bertholom
** Last update Wed Jul  1 20:35:03 2015 Alexis Bertholom
*/

#pragma once

#include <stdexcept>

class			GenericError : public std::runtime_error
{
public:
  enum			Type
    {
      Unknown = 0,
      InvalidWindowSize
    };

public:
  GenericError(GenericError::Type errcode);
  virtual ~GenericError() throw();

protected:
  GenericError::Type	_errcode;

private:
  static char const*	messages[];
};
