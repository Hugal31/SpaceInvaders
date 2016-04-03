//
// Created by laloge_h on 02/04/2016.
//

#include <algorithm>
#include <vector>
#include "Column.hh"

const Uint	moveCooldown = 50;

Column::Column(std::vector<Image> &sprites, Uint x, Uint nbEnemies)
  : _direction (RIGHT)
  , _x (x)
{
  for (Uint i = 0; i < nbEnemies; i++)
  {
    _enemies.push_back(Enemy(sprites[rand() % sprites.size()], 1, 1));
  }
  _firstTick = SDL_GetTicks();
  _timeLeft = 0;
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

  // Faites pas gaffe à cette ligne ;)
  Uint maxSize = std::max_element(_enemies.begin(), _enemies.end(), [] (const Enemy &a, const Enemy &b) -> bool { return a.w() < b.w(); } )->w();

  while (_timeLeft > moveCooldown)
  {
    if (_direction == RIGHT)
    {
      if (_x + maxSize + speed < maxX)
      {
	_x += speed;
      }
      else
      {
	_x = maxX - maxSize;
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
