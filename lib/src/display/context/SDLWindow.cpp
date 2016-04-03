/*
** SDLWindow.cpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 11:53:21 2015 Alexis Bertholom
** Last update Wed Jul  1 20:32:29 2015 Alexis Bertholom
*/

#include <SDL2/SDL.h>
#include "SDLWindow.hh"
#include "SDLError.hh"
#include "GenericError.hh"

SDLWindow::SDLWindow(char const* title,
		     Uint x, Uint y,
		     Uint w, Uint h,
		     Uint32 flags,
		     SDLContext const&)
  : _w(w), _h(h)
{
  if (w <= 0 || w > 3840 || h <= 0 || h > 2160)
    throw (GenericError(GenericError::InvalidWindowSize));
  this->_ratio = w / static_cast<float>(h);
  this->_window = SDL_CreateWindow(title, x, y, w, h, flags);
  if (!(this->_window))
    throw (SDLError("Window creation failed"));
}

SDLWindow::~SDLWindow()
{
  SDL_DestroyWindow(this->_window);
}
