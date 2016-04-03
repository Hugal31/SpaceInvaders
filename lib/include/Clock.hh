/*
** Clock.hh for libptr
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Wed Jul  8 18:21:47 2015 Alexis Bertholom
** Last update Thu Jul  9 15:26:53 2015 Alexis Bertholom
*/

#pragma once

#include <thread>
#include <chrono>

class		Clock
{
public:
  Clock() : _frameDuration(0) {}
  ~Clock() {}

public:
  void		sleep(std::chrono::milliseconds duration);
  bool		isFrameOver();
  bool		isFrameOver(std::chrono::milliseconds frameDuration);
  bool		isFrameOverSetNext(std::chrono::milliseconds nextFrameDuration);
  void		waitNextFrame();
  void		waitNextFrame(std::chrono::milliseconds frameDuration);
  void		startFrame();
  void		startFrame(std::chrono::milliseconds frameDuration);
  void		setFrameDuration(std::chrono::milliseconds frameDuration);

private:
  std::chrono::milliseconds _frameDuration;
  std::chrono::system_clock::time_point _lastTime;
};

inline void	Clock::sleep(std::chrono::milliseconds duration)
{
  std::this_thread::sleep_for(duration);
}

inline bool	Clock::isFrameOver()
{
  return (this->isFrameOver(this->_frameDuration));
}

inline bool	Clock::isFrameOver(std::chrono::milliseconds frameDuration)
{
  std::chrono::system_clock::time_point now(std::chrono::system_clock::now());
  std::chrono::milliseconds elapsed(std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_lastTime));

  if (frameDuration >= elapsed)
    return (false);
  this->_lastTime = std::chrono::system_clock::now();
  return (true);
}

inline bool	Clock::isFrameOverSetNext(std::chrono::milliseconds nextFrameDuration)
{
  if (isFrameOver())
    {
      this->_frameDuration = nextFrameDuration;
      return (true);
    }
  return (false);
}

inline void	Clock::waitNextFrame()
{
  this->waitNextFrame(this->_frameDuration);
}

inline void	Clock::waitNextFrame(std::chrono::milliseconds frameDuration)
{
  std::chrono::system_clock::time_point now(std::chrono::system_clock::now());
  std::chrono::milliseconds elapsed(std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_lastTime));

  std::this_thread::sleep_for(frameDuration - elapsed);
  this->_lastTime = std::chrono::system_clock::now();
}

inline void	Clock::startFrame()
{
  this->_lastTime = std::chrono::system_clock::now();
}

inline void	Clock::startFrame(std::chrono::milliseconds frameDuration)
{
  this->_lastTime = std::chrono::system_clock::now();
  this->_frameDuration = frameDuration;
}

inline void	Clock::setFrameDuration(std::chrono::milliseconds frameDuration)
{
  this->_frameDuration = frameDuration;
}
