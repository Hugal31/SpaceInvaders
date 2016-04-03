//
// Created by laloge_h on 02/04/2016.
//

#ifndef PONG_COLUMN_HH
#define PONG_COLUMN_HH

#include <list>
#include <vector>
#include "Enemy.hh"
#include "Laser.hh"

class Column
{
private:
    enum Direction {
	LEFT,
	RIGHT
    };

public:
    Column(std::vector<Image> &sprites, Uint x, Uint nbEnemies);
    ~Column();

    void display(SDLDisplay &display);
    void move(Uint speed, Uint maxX);
    void checkCollisions(std::list<Laser> &lasers);

private:
    std::vector<Enemy> _enemies;
    Direction _direction;
    Uint _x;
    Uint _y;
    Uint _firstTick;
    Uint _timeLeft;
};


#endif //PONG_COLUMN_HH
