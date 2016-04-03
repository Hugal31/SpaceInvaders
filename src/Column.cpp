//
// Created by laloge_h on 02/04/2016.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include "Column.hh"

const Uint	moveCooldown = 50;

Column::Column(std::vector<Image> &sprites, Uint x, Uint nbEnemies)
  : _direction (RIGHT)
  , _x (x)
  , _y (0)
  , _lastShoot (SDL_GetTicks())
  , _shootCooldown ((rand() % 5 + 2) * 1000) // Entre 2 et 7 secondes
{
  for (Uint i = 0; i < nbEnemies; i++)
  {
    _enemies.push_back(Enemy(sprites[rand() % sprites.size()], 1, 1));
  }
  _firstTick = SDL_GetTicks();
  _timeLeft = 0;

  // Faites pas gaffe à cette ligne, elle récupère la plus grande largeur des enemies ;)
  _width = std::max_element(_enemies.begin(), _enemies.end(), [] (const Enemy &a, const Enemy &b) -> bool { return a.w() < b.w(); } )->w();
}

Column::~Column()
{

}

void Column::display(SDLDisplay &display)
{
  Uint y = _y;

  for (Enemy &enemy : _enemies)
  {
    enemy.display(display, _x, y);
    y += enemy.h() + 10;
  }
}

void Column::move(Uint speed, Uint maxX)
{
  Uint lastTick = SDL_GetTicks();
  _timeLeft += lastTick - _firstTick;
  _firstTick = lastTick;

  while (_timeLeft > moveCooldown)
  {
    if (_direction == RIGHT)
    {
      if (_x + _width + speed < maxX)
      {
	_x += speed;
      }
      else
      {
	_x = maxX - _width;
	_direction = LEFT;
	_y += 10;
      }
    }
    else
    {
      if (_x >= speed)
      {
	_x -= speed;
      }
      else
      {
	_x = 0;
	_y += 10;
	_direction = RIGHT;
      }
    }
    _timeLeft -= moveCooldown;
  }
}

void Column::shoot(std::list<Laser> &lasers)
{
  Uint lastTick = SDL_GetTicks();

  while (lastTick - _lastShoot > _shootCooldown)
  {
    std::clog << "Enemies shoot" << std::endl;

    Uint y = _y;
    Uint tmp = _y;
    for (Enemy &enemy : _enemies)
    {
      tmp += enemy.h();
      if (enemy.isAlive())
      {
	y = tmp;
      }
      tmp += 10;
    }
    lasers.push_back(Laser(_x + _width / 2, y, Laser::DOWN));
    _lastShoot += _shootCooldown;
    _shootCooldown = (rand() % 5 + 2) * 1000;
  }
}

void Column::checkCollisions(std::list<Laser> &lasers)
{
  Uint y = _y;

  for (Enemy &enemy : _enemies)
  {
    if (enemy.isAlive())
    {
      auto it = lasers.begin();

      while (it != lasers.end())
      {
	if (!((it->x() >= _x + enemy.w())
	      || (it->x() + it->w() <= _x)
	      || (it->y() >= y + enemy.h())
	      || (it->y() + it->h() <= y)))
	{
	  enemy.hit();
	  it = lasers.erase(it);
	}
	else
	  it++;
      }
    }
    y += enemy.h() + 10;
  }
}
