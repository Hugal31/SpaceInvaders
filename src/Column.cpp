//
// Created by laloge_h on 02/04/2016.
//

#include <vector>
#include "Column.hh"

const Uint	moveTime = 500;

Column::Column(std::vector<Image> &sprites, Uint x, Uint nbEnemies)
  : _x (x)
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
  for (Uint y = 0; y < _enemies.size(); y++)
  {
    _enemies[y].display(display, _x, y * 50);
  }
}

void Column::run(Uint speed)
{
  Uint lastTick = SDL_GetTicks();
  _timeLeft += lastTick - _firstTick;
  _firstTick = lastTick;

  while (_timeLeft > moveTime)
  {
    _x += speed;
    _timeLeft -= moveTime;
  }
}
