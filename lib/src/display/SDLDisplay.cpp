/*
** SDLDisplay.cpp for libcodingclub in /home/thepatriot/repos/jd-protected/codingclub-priv/libs
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue Jan 27 12:19:41 2015 Alexis Bertholom
** Last update Wed Jul  1 20:33:16 2015 Alexis Bertholom
*/

#include "SDLError.hh"
#include "SDLDisplay.hh"

SDLDisplay::SDLDisplay(std::string const& winTitle,
		       Uint winW, Uint winH, Uint winX, Uint winY)
  : SDLContext(SDL_INIT_VIDEO),
    SDLWindow(winTitle.c_str(), winX, winY, winW, winH, 0, *this)
{
  SDL_Surface*	screen(SDL_GetWindowSurface(this->SDLWindow::get()));

  if (!screen)
    throw (SDLError("SDL_GetWindowSurface failed"));
  this->_screen = new Image(screen, Image::Wrap);
}

SDLDisplay::~SDLDisplay()
{
  delete (this->_screen);
}
