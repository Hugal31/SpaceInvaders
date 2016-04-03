//
// Created by laloge_h on 03/04/2016.
//

#ifndef PONG_SHOOTER_HH
#define PONG_SHOOTER_HH

#include <SDLDisplay.hh>
#include <Image.hh>
#include <list>
#include "Laser.hh"

class Shooter
{
public:
    Shooter(Uint maxX, Uint maxY);
    ~Shooter();

    void display(SDLDisplay &display);
    void move(bool left, bool right, Uint speed, Uint maxX);
    void shoot(bool key, std::list<Laser> &shoots);

private:
    Image _sprite;
    Uint _x;
    const Uint _y;

    Uint _timeLeftMove;
    Uint _firstTickMove;
    Uint _lastTimeShoot;
};


#endif //PONG_SHOOTER_HH
