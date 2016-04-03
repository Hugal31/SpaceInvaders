/*
** TronPacket.hh for libtron
**
** Made by Alexis Bertholom
** Login   bertho_d
** Email   <alexis.bertholom.jd@gmail.com>
**
** Started on  Wed Jul  1 20:34:33 2015 Alexis Bertholom
** Last update Fri Jul 10 10:35:48 2015 Alexis Bertholom
*/

#pragma once

#include <cstddef>

typedef unsigned int Uint;

struct		TronPacket
{
public:
  enum		Type
    {
      PlayerPosition = 1,
      PlayerDirection,
      PlayerEvDeath,
      PlayerEvLeave,

      PlayerEvJoin,
      PlayerEvWin,
      GameEvStopped,
      GameEvStarted,

      String
    };

  enum		Direction
    {
      Right = 0,
      Left
    };

  struct	PlayerPos
  {
    size_t	pos[2];
    Uint	id;
  };

  struct	PlayerEvent
  {
    Type	type;
    Uint	id;
  };

public:
  Type		type;
  union
  {
    PlayerPos	pos;
    Uint	id;
    Direction	dir;
    size_t	size;
  }		data;
};
