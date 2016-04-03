//
// Created by laloge_h on 02/04/2016.
//

#ifndef PONG_SPACEINVADERS_HH
#define PONG_SPACEINVADERS_HH

#include <SDLDisplay.hh>
#include <Input.hh>
#include <list>
#include <vector>
#include "Laser.hh"

class SpaceInvaders
{
public:
    SpaceInvaders();
    ~SpaceInvaders();

    void run();

private:
    SDLDisplay _display;
    Input _input;

private:
    Image _shootSprite;
    std::vector<Image> _enemiesSprites;
    std::list<Laser> _lasers;
};


#endif //PONG_SPACEINVADERS_HH
