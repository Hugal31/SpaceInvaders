/*
** Input.cpp for libptrgl in /home/thepatriot/repos/libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 11:48:01 2015 Alexis Bertholom
** Last update Thu Jul  9 01:48:51 2015 Alexis Bertholom
*/

#include <cstring>
#include <SDL2/SDL.h>
#include "SDLWindow.hh"
#include "Input.hh"

Input::Input(SDLContext const&)
{
  memset(this, 0, sizeof(Input));
}

Input::Input(GridDisplay const&)
{
  memset(this, 0, sizeof(Input));
}

/*
** public:
*/

float const*	Input::getMousePosNormalized(SDLWindow const& win) const
{
  static float	pos[2];

  pos[0] = ((this->_mousePos[0] << 1) / static_cast<float>(win.w())) - 1.0f;
  pos[1] = 1.0f - ((this->_mousePos[1] << 1) / static_cast<float>(win.h()));
  return (pos);
}

bool		Input::popMouseClickRel(MouseButton button)
{
  if (this->_mouseClicksRel[button])
    {
#ifndef NO_THREADS
      this->_lock.lock();
#endif
      this->_mouseClicksRel[button] -= 1;
#ifndef NO_THREADS
      this->_lock.unlock();
#endif
      return (true);
    }
  return (false);
}

Uint		Input::getMouseClicksRel(MouseButton button)
{
  Uint		res;

#ifndef NO_THREADS
  this->_lock.lock();
#endif
  res = this->_mouseClicksRel[button];
  this->_mouseClicksRel[button] = 0;
#ifndef NO_THREADS
  this->_lock.unlock();
#endif
  return (res);
}

bool		Input::popKeyReleaseRel(SDL_Scancode key)
{
  if (this->_keysReleaseRel[key])
    {
#ifndef NO_THREADS
      this->_lock.lock();
#endif
      this->_keysReleaseRel[key] -= 1;
#ifndef NO_THREADS
      this->_lock.unlock();
#endif
      return (true);
    }
  return (false);
}

Uint		Input::getKeyReleaseRel(SDL_Scancode key)
{
  Uint		res;

#ifndef NO_THREADS
  this->_lock.lock();
#endif
  res = this->_keysReleaseRel[key];
  this->_keysReleaseRel[key] = 0;
#ifndef NO_THREADS
  this->_lock.unlock();
#endif
  return (res);
}

bool		Input::popKeyPressRel(SDL_Scancode key)
{
  if (this->_keysPressRel[key])
    {
#ifndef NO_THREADS
      this->_lock.lock();
#endif
      this->_keysPressRel[key] -= 1;
#ifndef NO_THREADS
      this->_lock.unlock();
#endif
      return (true);
    }
  return (false);
}

Uint		Input::getKeyPressRel(SDL_Scancode key)
{
  Uint		res;

#ifndef NO_THREADS
  this->_lock.lock();
#endif
  res = this->_keysPressRel[key];
  this->_keysPressRel[key] = 0;
#ifndef NO_THREADS
  this->_lock.unlock();
#endif
  return (res);
}

void		Input::flushEvents()
{
  SDL_Event	event;

#ifndef NO_THREADS
  this->_lock.lock();
#endif
  memset(this->_mouseClicksRel, 0, sizeof(this->_mouseClicksRel));
  memset(this->_keysReleaseRel, 0, sizeof(this->_keysReleaseRel));
  memset(this->_keysPressRel, 0, sizeof(this->_keysPressRel));
  this->_mouseRel[0] = 0;
  this->_mouseRel[1] = 0;
  while (SDL_PollEvent(&event))
    switch (event.type)
      {
      case SDL_KEYUP:
      case SDL_KEYDOWN:
	this->handleKeyEvent(event);
	break ;
      case SDL_MOUSEBUTTONUP:
      case SDL_MOUSEBUTTONDOWN:
	this->handleMouseButtonEvent(event);
	break ;
      case SDL_MOUSEMOTION:
	this->setMouse(event.motion);
	break ;
      case SDL_WINDOWEVENT:
	if (event.window.event == SDL_WINDOWEVENT_CLOSE)
	  this->_exit = true;
	break ;
      default:
	break ;
      }
#ifndef NO_THREADS
  this->_lock.unlock();
#endif
}

/*
** private:
*/

void		Input::handleKeyEvent(SDL_Event const& ev)
{
  if (ev.key.repeat)
    return ;
  if (ev.type == SDL_KEYDOWN)
    {
      this->_keysState[ev.key.keysym.scancode] = true;
      this->_keysPressRel[ev.key.keysym.scancode] += 1;
    }
  else
    {
      this->_keysState[ev.key.keysym.scancode] = false;
      this->_keysReleaseRel[ev.key.keysym.scancode] += 1;
    }
}

void		Input::handleMouseButtonEvent(SDL_Event const& ev)
{
  if (ev.type == SDL_MOUSEBUTTONDOWN)
    this->_mouseButtonsState[ev.button.button] = true;
  else
    {
      this->_mouseButtonsState[ev.button.button] = false;
      this->_mouseClicksRel[ev.button.button] += 1;
    }
}

void		Input::setMouse(SDL_MouseMotionEvent const& motion)
{
  this->_mousePos[0] = motion.x;
  this->_mousePos[1] = motion.y;
  this->_mouseRel[0] = motion.xrel;
  this->_mouseRel[1] = motion.yrel;
}
