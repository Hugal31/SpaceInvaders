/*
** GridDisplay.hh for libcodingclub in /home/thepatriot/repos/jd-protected/codingclub-priv/libs
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Fri Jun 26 17:02:09 2015 Alexis Bertholom
** Last update Wed Jul  8 20:37:32 2015 Alexis Bertholom
*/

#include "types.hh"
#include "SDLDisplay.hh"

#pragma once

class		GridDisplay : protected SDLDisplay
{
public:
  GridDisplay(std::string const& winTitle,
	      Uint gridW = 100, Uint gridH = 100, Uint caseSize = 8) :
    SDLDisplay(winTitle, gridW * caseSize, gridH * caseSize),
    _gridW(gridW),
    _gridH(gridH),
    _caseSize(caseSize) {}
  ~GridDisplay() {}

public:
  int		setCase(Uint x, Uint y, Color color);
  Uint		w() const;
  Uint		h() const;
  Uint		c() const;

public:
  using		SDLDisplay::clearScreen;
  using		SDLDisplay::refreshScreen;

private:
  Uint		_gridW;
  Uint		_gridH;
  Uint		_caseSize;
};

inline int	GridDisplay::setCase(Uint x, Uint y, Color color)
{
  if (x < this->_gridW && y < this->_gridH)
    return (this->putRect(x * this->_caseSize, y * this->_caseSize,
			  this->_caseSize, this->_caseSize, color));
  return (0);
}

inline Uint	GridDisplay::w() const
{
  return (this->_gridW);
}

inline Uint	GridDisplay::h() const
{
  return (this->_gridH);
}

inline Uint	GridDisplay::c() const
{
  return (this->_caseSize);
}
