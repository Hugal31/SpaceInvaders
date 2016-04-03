/*
** StdError.hh for NetSoul++
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Tue May 26 21:41:22 2015 Alexis Bertholom
** Last update Wed Jul  1 22:27:36 2015 Alexis Bertholom
*/

#pragma once

#include <stdexcept>
#include <string>

class		StdError : public std::runtime_error
{
public:
  StdError();
  StdError(std::string const& error);
  virtual ~StdError() throw() {}

public:
  int		getErrorCode() const;

private:
  int		_code;
};

inline int	StdError::getErrorCode() const
{
  return (this->_code);
}
