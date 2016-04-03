//
// Created by laloge_h on 02/04/2016.
//

#ifndef PONG_SPACEINVADERS_HH
#define PONG_SPACEINVADERS_HH

#include <SDLDisplay.hh>
#include <Input.hh>
#include <vector>

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
    std::vector<Image> _enemiesSprites;
};


#endif //PONG_SPACEINVADERS_HH
