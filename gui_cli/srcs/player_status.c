#include "commands.h"

int	player_expulsing(t_display *d, char **tab)
{
  int	i;

  if (!tab[1])
    return (-1);
  i = get_player(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->players[i].status = BUMPING;
  d->players[i].status_time = 0;
  return (0);
}

int	player_broadcasting(t_display *d, char **tab)
{
  int	i;

  if (!tab[1])
    return (-1);
  i = get_player(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->players[i].status = TALKING;
  d->players[i].status_time = 0;
  return (0);
}

int	player_incantating(t_display *d, char **tab)
{
  int	i;
  int	j;

  if (!tab[1] || !tab[2])
    return (-1);
  i = 0;
  while (i < 1000)
    {
      j = 3;
      while (tab[j])
	{
	  if (d->players[i].id == atoi(tab[j]))
	    {
	      d->players[i].status = INCANTATING;
	      d->players[i].status_time = 0;
	    }
	  j++;
	}
      i++;
    }
  return (0);
}

int	player_incantating_end(t_display *d, char **tab)
{
  int	i;

  if (!tab[1] || !tab[2])
    return (-1);
  i = 0;
  while (i < 1000)
    {
      if (d->players[i].id != -1 &&
	  d->players[i].pos.x == atoi(tab[1]) &&
	  d->players[i].pos.y == atoi(tab[2]) &&
	  d->players[i].status == INCANTATING)
	{
	  d->players[i].status = IDLE;
	  d->players[i].status_time = 0;
	}
      i++;
    }
  return (0);
}

int	player_forking(__attribute__((unused)) t_display *d,
		       __attribute__((unused)) char **tab)
{
  return (0);
}
