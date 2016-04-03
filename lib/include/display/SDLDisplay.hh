/*
** SDLDisplay.hh for libcodingclub in /home/thepatriot/repos/jd-protected/codingclub-priv/libs
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue Jan 27 12:06:35 2015 Alexis Bertholom
** Last update Mon Jul  6 20:55:58 2015 Alexis Bertholom
*/

#pragma once

#include <string>
#include <SDL2/SDL.h>
#include "SDLContext.hh"
#include "SDLWindow.hh"
#include "Image.hh"

class		SDLDisplay : public SDLContext, protected SDLWindow
{
public:
  SDLDisplay(std::string const& winTitle,
	     Uint winW,
	     Uint winH,
	     Uint winX = SDL_WINDOWPOS_UNDEFINED,
	     Uint winY = SDL_WINDOWPOS_UNDEFINED);
  ~SDLDisplay();

public:
  int		putPixel(Uint x, Uint y, Color color);
  int		putRect(Uint x, Uint y, Uint w, Uint h, Color color);
  int		putImage(Uint x, Uint y, Image& img, Uint w, Uint h);
  int		clearScreen();
  int		fillScreen(Color color);
  int		refreshScreen();

public:
  using		SDLWindow::w;
  using		SDLWindow::h;

private:
  Image*	_screen;
};

inline int	SDLDisplay::putPixel(Uint x, Uint y, Color color)
{
  return (this->_screen->putPixel(x, y, color));
}

inline int	SDLDisplay::putRect(Uint x, Uint y, Uint w, Uint h, Color color)
{
  return (this->_screen->putRect(x, y, w, h, color));
}

inline int	SDLDisplay::putImage(Uint x, Uint y, Image& img, Uint w, Uint h)
{
  return (this->_screen->blit(x, y, img, w, h));
}

inline int	SDLDisplay::clearScreen()
{
  return (this->_screen->clear());
}

inline int	SDLDisplay::fillScreen(Color color)
{
  return (this->_screen->fill(color));
}

inline int	SDLDisplay::refreshScreen()
{
  return (SDL_UpdateWindowSurface(this->SDLWindow::get()));
}
