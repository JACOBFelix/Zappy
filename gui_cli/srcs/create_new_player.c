#include <string.h>
#include "commands.h"

int	create_new_player(t_display *d, char **tab)
{
  int	i;

  i = 0;
  while (i < 7)
    {
      if (!tab[i])
	return (-1);
      i++;
    }
  d->players[d->nb_players].id = atoi(tab[1]);
  d->players[d->nb_players].pos.x = atoi(tab[2]);
  d->players[d->nb_players].pos.y = atoi(tab[3]);
  d->players[d->nb_players].dir = atoi(tab[4]);
  d->players[d->nb_players].lv = atoi(tab[5]);
  d->players[d->nb_players].team_name =
    malloc(sizeof(char) * strlen(tab[6]));
  if (d->players[d->nb_players].team_name == NULL)
    return (-1);
  strcpy(d->players[d->nb_players].team_name, tab[6]);
  d->nb_players++;
  return (0);
}
