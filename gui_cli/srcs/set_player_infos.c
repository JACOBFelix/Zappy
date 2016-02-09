#include "commands.h"

int	set_player_position(t_display *d, char **tab)
{
  int	i;

  if (!tab[1] || !tab[2] || !tab[3])
    return (-1);
  i = get_player(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  if (d->players[i].pos.x == atoi(tab[2])
    && d->players[i].pos.y == atoi(tab[3]))
  {
    d->players[i].dir = atoi(tab[4]);
    return (0);
  }
  d->players[i].status = WALKING;
  d->players[i].new_pos.x = atoi(tab[2]);
  d->players[i].new_pos.y = atoi(tab[3]);
  d->players[i].dir = atoi(tab[4]);
  return (0);
}

int	set_player_level(t_display *d, char **tab)
{
  int	i;

  if (!tab[1] || !tab[2])
    return (-1);
  i = get_player(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->players[i].lv = atoi(tab[2]);
  return (0);
}

int	set_player_inventory(t_display *d, char **tab)
{
  int	i;
  int	n;

  if (!tab[1] || !tab[2] || !tab[3])
    return (-1);
  i = get_player(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->players[i].pos.x = atoi(tab[2]);
  d->players[i].pos.y = atoi(tab[3]);
  n = 0;
  while (n < 7)
    {
      if (!tab[4 + n])
	return (-1);
      d->players[i].resources[n] = atoi(tab[4 + n]);
      n++;
    }
  return (0);
}
