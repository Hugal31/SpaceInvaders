//
// Created by laloge_h on 03/04/2016.
//

#ifndef PONG_LASER_HH
#define PONG_LASER_HH

#include <SDLDisplay.hh>
#include <Image.hh>

class Laser
{
public:
    enum Direction
    {
	UP,
	DOWN
    };

public:
    Laser(Uint x, Uint y, Direction direction);
    ~Laser();

    void display(SDLDisplay &display);
    void move();

private:
    const Direction _direction;
    const Uint _x;
    Uint _y;
    Uint _timeLeftMove;
    Uint _firstTickMove;
};


#endif //PONG_LASER_HH
