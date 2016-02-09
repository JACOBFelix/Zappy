#define _GNU_SOURCE
#include <stdio.h>
#include "network.h"

char		*mail_handle_connect_nbr(t_server *infos, t_mail *msg)
{
  int const	idx = find_team_from_name(infos, msg->from->team_name);
  char		*str;

  if (idx < 0)
    return (NULL);
  if (asprintf(&str, "%i\n",
	       (int)infos->clients_by_team
	       - (int)infos->nb_players_team[idx]) < 0)
    return (NULL);
  return (str);
}
