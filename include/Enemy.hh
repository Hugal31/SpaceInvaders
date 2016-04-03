//
// Created by laloge_h on 02/04/2016.
//

#ifndef PONG_ENEMY_HH
#define PONG_ENEMY_HH


#include <Image.hh>
#include <display/SDLDisplay.hh>

class Enemy
{
public:
    Enemy(Image &sprite, int pv, int damage);
    ~Enemy();

    void display(SDLDisplay &, Uint x, Uint y);

    Uint w() const { return _sprite.w(); }

private:
    Image &_sprite;
    int _pv;
    int _damage;
};


#endif //PONG_ENEMY_HH
