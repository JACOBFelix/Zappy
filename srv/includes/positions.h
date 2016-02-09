#ifndef POSITIONS_H_
# define POSITIONS_H_

# include <stdint.h>

typedef struct	s_pos
{
  int32_t	x;
  int32_t	y;
}		t_pos;

typedef enum	e_dir
  {
    NORTH = 1,
    EST = 2,
    SOUTH = 3,
    WEST = 4
  }		t_dir;

typedef struct	s_dir_expulse
{
  t_dir		kicker;
  t_dir		kicked;
  int		value;
}		t_dir_expulse;

#endif /* !POSITIONS_H_ */
