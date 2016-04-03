/*
** Image.hh for libcodingclub in /home/thepatriot/repos/jd-protected/codingclub-priv/libs
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue Jan 27 12:37:23 2015 Alexis Bertholom
** Last update Thu Jul  2 15:13:49 2015 Alexis Bertholom
*/

#pragma once

#include "types.hh"

struct			SDL_Surface;

class			Image
{
public:
  enum			Type
    {
      Wrap,
      Copy
    };

public:
  Image(Uint w, Uint h);
  Image(SDL_Surface* img, Image::Type type = Image::Copy);
  ~Image();

public:
  int			putPixel(Uint x, Uint y, Color color);
  int			putRect(Uint x, Uint y, Uint w, Uint h, Color color);
  int			blit(Uint x, Uint y, Image& img, Uint w, Uint h);
  int			clear();
  int			fill(Color color);

public:
  SDL_Surface*		getSurface();
  SDL_Surface const*	getSurface() const;
  Uint			w() const;
  Uint			h() const;

private:
  SDL_Surface*		_img;
  bool			_allocd;
  Uint			_w;
  Uint			_h;
  Uint			_size;
};

inline SDL_Surface*	Image::getSurface()
{
  return (this->_img);
}

inline SDL_Surface const* Image::getSurface() const
{
  return (this->_img);
}

inline Uint		Image::w() const
{
  return (this->_w);
}

inline Uint		Image::h() const
{
  return (this->_h);
}
