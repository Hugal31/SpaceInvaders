/*
** FileError.hh for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 12:02:59 2015 Alexis Bertholom
** Last update Wed Jul  1 20:35:00 2015 Alexis Bertholom
*/

#pragma once

#include <stdexcept>

class			FileError : public std::runtime_error
{
public:
  enum			Type
    {
      Unknown = 0,
      OpenError,
      ReadError,
      BadShader,
      BadGLProgram
    };

public:
  FileError(FileError::Type errcode, char const* filename = NULL);
  virtual ~FileError() throw();

protected:
  FileError::Type	_errcode;

private:
  static char const*	messages[];
};
