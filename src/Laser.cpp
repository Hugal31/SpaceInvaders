//
// Created by laloge_h on 03/04/2016.
//

#include <SDL2/SDL.h>
#include <SDLDisplay.hh>
#include "Laser.hh"

static Uint moveCooldown = 1000 / 60;

Laser::Laser(Uint x, Uint y, Direction direction)
  : _direction (direction)
  , _x (x)
  , _y (y)
  , _timeLeftMove (0)
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

void Laser::move()
{
  Uint lastTick = SDL_GetTicks();
  _timeLeftMove += lastTick - _firstTickMove;
  _firstTickMove = lastTick;

  while (_timeLeftMove > moveCooldown)
  {
    if (_direction == UP)
    {
      _y -= 2;
    }
    else
    {
      _y += 2;
    }
    _timeLeftMove -= moveCooldown;
  }
}
