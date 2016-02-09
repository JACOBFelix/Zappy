#ifndef PLAYER_ACTIONS_H_
# define PLAYER_ACTIONS_H_

# include "positions.h"

typedef enum	e_incantation_join
  {
    JOINABLE,
    UNJOINABLE
  }		t_incantation_join;

typedef struct		s_incantation
{
  t_pos			pos;
  int			success;
  t_player		**player;
}			t_incantation;

#endif /* !PLAYER_ACTIONS_H_ */
