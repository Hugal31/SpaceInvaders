//
// Created by laloge_h on 03/04/2016.
//

#include <iostream>
#include "Shooter.hh"

const Uint moveTime = 1000 / 60;

Shooter::Shooter(Uint maxX, Uint maxY) try
  : _sprite (SDL_LoadBMP("resources/shooter.bmp"), Image::Wrap)
  , _x ((maxX - _sprite.w()) / 2)
  , _y (maxY - _sprite.h())
  , _firstTick (SDL_GetTicks())
  , _timeLeft (0)
{

}
catch (...)
{
  std::cerr << SDL_GetError() << std::endl;
}

Shooter::~Shooter()
{

}

void Shooter::move(bool left, bool right, Uint speed, Uint maxX)
{
  Uint lastTick = SDL_GetTicks();
  _timeLeft += lastTick - _firstTick;
  _firstTick = lastTick;
  while (_timeLeft > moveTime)
  {
    if (right)
    {
      if (_x + speed + _sprite.w() < maxX)
	_x += speed;
    }
    if (left)
    {
      if (_x >= speed)
	_x -= speed;
    }
    _timeLeft -= moveTime;
  }
}

void Shooter::display(SDLDisplay &display)
{
  display.putImage(_x, _y, _sprite, _sprite.w(), _sprite.h());
}
