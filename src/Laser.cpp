//
// Created by laloge_h on 03/04/2016.
//

#include <SDL2/SDL.h>
#include <SDLDisplay.hh>
#include "Laser.hh"

Laser::Laser(Uint x, Uint y, Direction direction, Uint timeLeftMove)
  : _direction (direction)
  , _x (x)
  , _y (y)
  , _timeLeftMove (timeLeftMove)
  , _firstTickMove (SDL_GetTicks())
{

}

Laser::~Laser()
{

}

void Laser::display(SDLDisplay &display)
{
  static Image sprite(SDL_LoadBMP("resources/shoot.bmp"), Image::Wrap);

  display.putImage(_x, _y, sprite, sprite.w(), sprite.h());
}
