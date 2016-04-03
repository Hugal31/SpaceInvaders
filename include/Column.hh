//
// Created by laloge_h on 02/04/2016.
//

#ifndef PONG_COLUMN_HH
#define PONG_COLUMN_HH

#include <vector>
#include "Enemy.hh"

class Column
{
public:
    Column(std::vector<Image> &sprites, Uint x, Uint nbEnemies);
    ~Column();

    void display(SDLDisplay &display);
    void run(Uint speed);

private:
    std::vector<Enemy> _enemies;
    Uint _x;
    Uint _y;
    Uint _firstTick;
    Uint _timeLeft;
};


#endif //PONG_COLUMN_HH
