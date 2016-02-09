#include "commands.h"

int	player_dropping(t_display *d, char **tab)
{
  int	i;

  i = get_player(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->players[i].status = DROPPING;
  d->players[i].status_time = 0;
  return (0);
}

int	player_getting(t_display *d, char **tab)
{
  int	i;

  i = get_player(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->players[i].status = DROPPING;
  d->players[i].status_time = 0;
  return (0);
}

int	player_dying(t_display *d, char **tab)
{
  int	i;

  i = get_player(d, atoi(tab[1]));
  if (i < 0)
    return (-1);
  d->players[i].status = DEAD;
  return (0);
}
