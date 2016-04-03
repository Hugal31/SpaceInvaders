//
// Created by laloge_h on 03/04/2016.
//

#ifndef PONG_SHOOTER_HH
#define PONG_SHOOTER_HH

#include <SDLDisplay.hh>
#include <Image.hh>

class Shooter
{
public:
    Shooter(Uint maxX, Uint maxY);
    ~Shooter();

    void display(SDLDisplay &display);
    void move(bool left, bool right, Uint speed, Uint maxX);

private:
    Image _sprite;
    Uint _x;
    const Uint _y;

    Uint _timeLeft;
    Uint _firstTick;
};


#endif //PONG_SHOOTER_HH
