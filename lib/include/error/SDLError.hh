/*
** SDLError.hh for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 12:15:25 2015 Alexis Bertholom
** Last update Wed Jul  1 20:35:09 2015 Alexis Bertholom
*/

#pragma once

#include <stdexcept>

class		SDLError : public std::runtime_error
{
public:
  SDLError();
  SDLError(char const* error);
  virtual ~SDLError() throw();
};
