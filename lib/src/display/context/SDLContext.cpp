/*
** SDLContext.cpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 11:52:57 2015 Alexis Bertholom
** Last update Wed Jul  1 20:32:27 2015 Alexis Bertholom
*/

#include <SDL2/SDL.h>
#include "SDLError.hh"
#include "SDLContext.hh"

SDLContext::SDLContext(Uint32 flags)
{
  if (SDL_Init(flags) != 0)
    throw (SDLError("SDL initialization failed"));
}

SDLContext::~SDLContext()
{
  SDL_Quit();
}
