#ifndef EGG_H_
# define EGG_H_

# include <time.h>
# include "positions.h"

typedef enum	e_egg_type
  {
    OK = 0,
    KO
  }		t_egg_type;

typedef struct		s_egg
{
  char			*team_name;
  clock_t		time;
  t_pos			pos;
  uint32_t		id;
}			t_egg;

#endif /* !EGG_H_ */
