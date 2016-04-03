/*
** FileError.cpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 12:24:27 2015 Alexis Bertholom
** Last update Wed Jul  1 20:31:15 2015 Alexis Bertholom
*/

#include "FileError.hh"

char const*	FileError::messages[] = {
  "File error",
  "Can't access file",
  "Can't read file",
  "Invalid GLSL Shader file",
  "Failed to link GL program"
};

FileError::FileError(FileError::Type errcode, char const* filename)
  : std::runtime_error(filename ?
		       (std::string(filename) + ": " + FileError::messages[errcode]) :
		       (FileError::messages[errcode])), _errcode(errcode)
{
}

FileError::~FileError() throw()
{
}
