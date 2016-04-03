/*
** Input.hh for libptrgl
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Mar 27 11:39:19 2015 Alexis Bertholom
** Last update Thu Jul  9 01:47:27 2015 Alexis Bertholom
*/

#define NO_THREADS

#pragma once

#ifndef NO_THREADS
# include <mutex>
#endif

#include <SDL2/SDL_scancode.h>
#include "types.hh"

struct		SDL_MouseMotionEvent;
union		SDL_Event;
class		SDLWindow;
class		SDLContext;
class		GridDisplay;

class		Input
{
public:
  enum		MouseButton
    {
      MouseLeft = 1,
      MouseMiddle,
      MouseRight,
      MouseButton4,
      MouseButton5,
      MouseButton6,
      MouseButton7,
      NUM_MOUSE_BUTTONS
    };

public:
  Input(SDLContext const&);
  Input(GridDisplay const&);
  ~Input() {}

public:
  bool		getKeyState(SDL_Scancode key) const;
  bool		getMouseButtonState(MouseButton button) const;
  int const*	getMousePos() const;
  int const*	getMouseRel() const;
  bool		shouldExit() const;

  float const*	getMousePosNormalized(SDLWindow const& win) const;

  bool		popMouseClickRel(MouseButton button);
  Uint		getMouseClicksRel(MouseButton button);
  Uint		peekMouseClicksRel(MouseButton button) const;

  bool		popKeyReleaseRel(SDL_Scancode key);
  Uint		getKeyReleaseRel(SDL_Scancode key);
  Uint		peekKeyReleaseRel(SDL_Scancode key) const;
  bool		popKeyPressRel(SDL_Scancode key);
  Uint		getKeyPressRel(SDL_Scancode key);
  Uint		peekKeyPressRel(SDL_Scancode key) const;

  void		flushEvents();

private:
  void		handleKeyEvent(SDL_Event const& ev);
  void		handleMouseButtonEvent(SDL_Event const& ev);
  void		setMouse(SDL_MouseMotionEvent const& motion);

private:
  bool		_exit;
  bool		_mouseButtonsState[NUM_MOUSE_BUTTONS];
  bool		_keysState[SDL_NUM_SCANCODES];
  int		_mousePos[2];
  int		_mouseRel[2];
  Uint		_mouseClicksRel[NUM_MOUSE_BUTTONS];
  Uint		_keysReleaseRel[SDL_NUM_SCANCODES];
  Uint		_keysPressRel[SDL_NUM_SCANCODES];
#ifndef NO_THREADS
  std::mutex	_lock;
#endif
};

inline bool	Input::getKeyState(SDL_Scancode key) const
{
  return (this->_keysState[key]);
}

inline bool	Input::getMouseButtonState(MouseButton button) const
{
  return (this->_mouseButtonsState[button]);
}

inline int const* Input::getMousePos() const
{
  return (this->_mousePos);
}

inline int const* Input::getMouseRel() const
{
  return (this->_mouseRel);
}

inline bool	Input::shouldExit() const
{
  return (this->_exit);
}

inline Uint	Input::peekMouseClicksRel(MouseButton button) const
{
  return (this->_mouseClicksRel[button]);
}

inline Uint	Input::peekKeyReleaseRel(SDL_Scancode key) const
{
  return (this->_keysReleaseRel[key]);
}

inline Uint	Input::peekKeyPressRel(SDL_Scancode key) const
{
  return (this->_keysPressRel[key]);
}
