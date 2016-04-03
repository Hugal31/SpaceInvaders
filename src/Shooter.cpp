//
// Created by laloge_h on 03/04/2016.
//

#include <iostream>
#include "Shooter.hh"

const Uint moveCooldown = 1000 / 60;
const Uint shootCooldown = 1000;

Shooter::Shooter(Uint maxX, Uint maxY) try
  : _sprite (SDL_LoadBMP("resources/shooter.bmp"), Image::Wrap)
  , _x ((maxX - _sprite.w()) / 2)
  , _y (maxY - _sprite.h())
  , _firstTickMove (SDL_GetTicks())
  , _timeLeftMove (0)
  , _lastTimeShoot (SDL_GetTicks())
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
  _timeLeftMove += lastTick - _firstTickMove;
  _firstTickMove = lastTick;
  while (_timeLeftMove > moveCooldown)
  {
    if (right)
    {
      if (_x + speed + _sprite.w() < maxX)
	_x += speed;
      else
	_x = maxX - _sprite.w();
    }
    if (left)
    {
      if (_x >= speed)
	_x -= speed;
      else
	_x = 0;
    }
    _timeLeftMove -= moveCooldown;
  }
}

void Shooter::shoot(bool key, std::list<Laser> &shoots)
{
  Uint lastTick = SDL_GetTicks();

  if (key && _lastTimeShoot + shootCooldown < lastTick)
  {
    std::clog << "Shooter tire un laser" << std::endl;
    shoots.push_back(Laser(_x + _sprite.w() / 2, _y - Laser::sprite().h(), Laser::UP));
    _lastTimeShoot = lastTick;
  }
}

void Shooter::display(SDLDisplay &display)
{
  display.putImage(_x, _y, _sprite, _sprite.w(), _sprite.h());
}

bool Shooter::checkCollisions(std::list<Laser> &lasers)
{
  auto it = lasers.begin();

  while (it != lasers.end())
  {
    if (!((it->x() >= _x + _sprite.w())
	  || (it->x() + it->w() <= _x)
	  || (it->y() >= _y + _sprite.h())
	  || (it->y() + it->h() <= _y)))
    {
      std::clog << "Shooter détruit" << std::endl;
      it = lasers.erase(it);
    }
    else
      it++;
  }
  return false;
}
