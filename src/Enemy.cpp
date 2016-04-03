//
// Created by laloge_h on 02/04/2016.
//

#include <iostream>
#include "Enemy.hh"

Enemy::Enemy(Image &sprite, int pv, int damage)
  : _sprite (sprite)
  , _pv (pv)
  , _damage (damage)
{

}

Enemy::~Enemy()
{

}

void Enemy::display(SDLDisplay &display, Uint x, Uint y)
{
  if (_pv > 0)
    display.putImage(x, y, _sprite, _sprite.w(), _sprite.h());
}

void Enemy::hit()
{
  if (_pv > 0)
    _pv--;
}
