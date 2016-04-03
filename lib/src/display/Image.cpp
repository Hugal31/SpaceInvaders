/*
** Image.cpp for libcodingclub in /home/thepatriot/repos/jd-protected/codingclub-priv/libs
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue Jan 27 12:44:19 2015 Alexis Bertholom
** Last update Thu Jul  2 20:06:51 2015 Alexis Bertholom
*/

#include <cstring>
#include <SDL2/SDL.h>
#include "LogicError.hh"
#include "SDLError.hh"
#include "Image.hh"

Image::Image(Uint w, Uint h) : _allocd(true), _w(w), _h(h)
{
  if (!(this->_size = w * h))
    throw (LogicError(LogicError::InvalidParameters));
  if (!(this->_img = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0)))
    throw (SDLError("SDL surface creation failed"));
}

Image::Image(SDL_Surface* img, Image::Type type)
{
  if (!img || !(this->_w = img->w) || !(this->_h = img->h))
    throw (LogicError(LogicError::InvalidParameters));
  this->_size = this->_w * this->_h;
  if (type == Image::Wrap)
    {
      this->_allocd = false;
      this->_img = img;
      return ;
    }
  this->_allocd = true;
  if (!(this->_img = SDL_CreateRGBSurface(0, this->_w, this->_h, sizeof(Color) << 3, 0, 0, 0, 0)))
    throw (SDLError("SDL surface creation failed"));
  SDL_BlitSurface(img, NULL, this->_img, NULL);
}

Image::~Image()
{
  if (this->_allocd)
    SDL_FreeSurface(this->_img);
}

int		Image::putPixel(Uint x, Uint y, Color color)
{
  if (SDL_MUSTLOCK(this->_img) && SDL_LockSurface(this->_img) == -1)
    return (-1);
  if ((int)x < this->_img->w && (int)y < this->_img->h)
    *((Color*)this->_img->pixels + sizeof(Color) * (y * this->_img->w + x)) = color;
  if (SDL_MUSTLOCK(this->_img))
    SDL_UnlockSurface(this->_img);
  return (0);
}

int		Image::putRect(Uint x, Uint y, Uint w, Uint h, Color color)
{
  SDL_Rect	r = {
    static_cast<int>(x),
    static_cast<int>(y),
    static_cast<int>(w),
    static_cast<int>(h)
  };

  return (SDL_FillRect(this->_img, &r, color));
}

int		Image::blit(Uint x, Uint y, Image& img, Uint w, Uint h)
{
  SDL_Rect	r = {
    static_cast<int>(x),
    static_cast<int>(y),
    static_cast<int>(w),
    static_cast<int>(h)
  };

  return (SDL_BlitSurface(img.getSurface(), NULL, this->_img, &r));
}

int		Image::clear()
{
  if (SDL_MUSTLOCK(this->_img) && SDL_LockSurface(this->_img) == -1)
    return (-1);
  memset(this->_img->pixels, 0, this->_size * sizeof(Color));
  if (SDL_MUSTLOCK(this->_img))
    SDL_UnlockSurface(this->_img);
  return (0);
}

int		Image::fill(Color color)
{
  Color*	ptr = (Color*)this->_img->pixels;

  if (SDL_MUSTLOCK(this->_img) && SDL_LockSurface(this->_img) == -1)
    return (-1);
  for (Uint i = 0; i < this->_size; ++i)
    *(ptr++) = color;
  if (SDL_MUSTLOCK(this->_img))
    SDL_UnlockSurface(this->_img);
  return (0);
}
