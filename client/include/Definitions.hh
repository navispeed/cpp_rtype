/*
** trouve_b
*/

#ifndef DEFINITION_CLIENT_HH_
# define DEFINITION_CLIENT_HH_

#include <tuple>

namespace client
{
  enum	Team
    {
      PLAYER,
      ENEMY
    };

  enum	worldEventType
    {
      SPAWN,
      UPDATE,
      MOVE,
      DELETE
    };
}

typedef std::pair<int16_t, int16_t>	pos_t;
typedef std::pair<int16_t, int16_t>	vec_t;
typedef uint32_t			tick;
typedef uint16_t			ide_t;
typedef uint16_t			typeide_t;
typedef uint16_t			UIevent_t;

#endif
