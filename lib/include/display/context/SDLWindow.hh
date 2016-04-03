/*
** SDLWindow.hh for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 11:40:52 2015 Alexis Bertholom
** Last update Thu Jul  2 15:23:20 2015 Alexis Bertholom
*/

#pragma once

#include "types.hh"

struct		SDL_Window;
class		SDLContext;

class		SDLWindow
{
public:
  SDLWindow(char const* title,
	    Uint x, Uint y,
	    Uint w, Uint h,
	    Uint32 flags,
	    SDLContext const& context);
  ~SDLWindow();

public:
  SDL_Window*	get() const;
  int		w() const;
  int		h() const;

public:
  float		normalizeX(int x) const;
  float		normalizeY(int y) const;
  int		denormalizeX(float x) const;
  int		denormalizeY(float y) const;
  float		ratio() const;

private:
  Uint		_w;
  Uint		_h;
  float		_ratio;
  SDL_Window*	_window;
};

inline SDL_Window* SDLWindow::get() const
{
  return (this->_window);
}

inline int	SDLWindow::w() const
{
  return (this->_w);
}

inline int	SDLWindow::h() const
{
  return (this->_h);
}

inline float	SDLWindow::normalizeX(int x) const
{
  return (((x << 1) / static_cast<float>(this->_w)) - 1.0f);
}

inline float	SDLWindow::normalizeY(int y) const
{
  return (1.0f - ((y << 1) / static_cast<float>(this->_h)));
}

inline int	SDLWindow::denormalizeX(float x) const
{
  return (static_cast<int>((x + 1.0f) * this->_w) >> 1);
}

inline int	SDLWindow::denormalizeY(float y) const
{
  return (static_cast<int>((1.0f - y) * this->_h) >> 1);
}

inline float	SDLWindow::ratio() const
{
  return (this->_ratio);
}
