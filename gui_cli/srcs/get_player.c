#include "display.h"

/*
** Returns the player number as stocked in the display
** structure of the id passed as a parameter.
*/
int	get_player(t_display *d, int id)
{
  int	i;

  i = 0;
  while (i < 1000)
    {
      if (d->players[i].id == id)
	return (i);
      i++;
    }
  return (-1);
}

int	get_egg(t_display *d, int id)
{
  int	i;

  i = 0;
  while (i < 1000)
    {
      if (d->eggs[i].id == id)
	return (i);
      i++;
    }
  return (-1);
}
