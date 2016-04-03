/*
** SDLError.cpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 12:31:47 2015 Alexis Bertholom
** Last update Wed Jul  1 20:31:29 2015 Alexis Bertholom
*/

#include <SDL2/SDL.h>
#include "SDLError.hh"

SDLError::SDLError()
  : std::runtime_error(std::string("SDL error: ") + SDL_GetError())
{
}

SDLError::SDLError(char const* message)
  : std::runtime_error(message ?
		       (std::string("SDL error: ") + message + ": " + SDL_GetError()) :
		       (std::string("SDL error: ") + SDL_GetError()))
{
}

SDLError::~SDLError() throw()
{
}
