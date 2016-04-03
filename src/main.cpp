#include <unistd.h>
#include <iostream>
#include <ctime>
#include <SDLDisplay.hh>
#include <SpaceInvaders.hh>
//#include "SDLDisplay.hh"
#include "Input.hh"
#include "Colors.hpp"

using namespace std;

int		main(int argc, char **argv)
{
  SpaceInvaders spaceInvaders;

  srand(time(NULL));
  spaceInvaders.run();
  return (0);
}
