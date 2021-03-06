//
// Created by laloge_h on 02/04/2016.
//

#include <SDLDisplay.hh>
#include <Input.hh>
#include <iostream>
#include "Column.hh"
#include "Shooter.hh"
#include "SpaceInvaders.hh"

const Uint	imagePerSecond = 60;

SpaceInvaders::SpaceInvaders() try
  : _display ("Space invaders", 800, 600)
  , _input (_display)
  , _shootSprite (SDL_LoadBMP("resources/shoot.bmp"), Image::Wrap)
  , _enemiesSprites ({Image(SDL_LoadBMP("resources/pink.bmp"), Image::Wrap),
		     Image(SDL_LoadBMP("resources/blue.bmp"), Image::Wrap),
		     Image(SDL_LoadBMP("resources/yellow.bmp"), Image::Wrap)})
{
  std::cout << "Initialisation du space invader" << std::endl;
}
catch (...)
{
  std::cerr << SDL_GetError() << std::endl;
}

SpaceInvaders::~SpaceInvaders()
{
}

void SpaceInvaders::run()
{
  _display.clearScreen();

  Column column(_enemiesSprites, 0, 5);
  Shooter shooter(_display.w(), _display.h());

  while (!_input.shouldExit())
  {
    Uint32 firstTick = SDL_GetTicks();

    _input.flushEvents();

    // Display
    _display.clearScreen();
    column.display(_display);
    shooter.display(_display);
    for (Laser &laser : _lasers)
    {
      laser.display(_display);
    }
    _display.refreshScreen();

    // Handle user events
    shooter.move(_input.getKeyState(SDL_SCANCODE_A), _input.getKeyState(SDL_SCANCODE_D), 5, (Uint) _display.w());
    shooter.shoot(_input.getKeyState(SDL_SCANCODE_SPACE), _lasers);

    // Handle game events
    shooter.checkCollisions(_lasers);
    column.move(5, _display.w());
    column.shoot(_lasers);
    column.checkCollisions(_lasers);

    // On parcourt tous les lasers et on supprime ceux qui sont hors de l'écran
    auto it = _lasers.begin();
    while (it != _lasers.end())
    {
      it->move();
      if (it->y() > _display.h()
	  || it->y() + it->h() < 0)
      {
	std::clog << "Delete laser" << std::endl;
	it = _lasers.erase(it);
      }
      else
	it++;
    }

    Uint32 lastTick = SDL_GetTicks();
    if (lastTick - firstTick < 1000 / imagePerSecond)
      SDL_Delay((1000 / imagePerSecond) - lastTick + firstTick);
  }
}
