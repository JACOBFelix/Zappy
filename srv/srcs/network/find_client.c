#include <string.h>
#include "network.h"

t_player	*find_player_from_id(t_server *infos, int id)
{
  t_list	*client;

  for (client = infos->network.client; client != NULL; client = client->next)
    if (((t_player *)client->data)->fd == id)
      return (client->data);
  return (NULL);
}

int		find_team_from_name(t_server *infos, char *team_name)
{
  uint32_t	i;

  if (team_name == NULL)
    return (-1);
  for (i = 0; i < infos->nb_teams; ++i)
    {
      if (strcmp(infos->teams_names[i], team_name) == 0)
	return (i);
    }
  return (-1);
}

t_egg		*find_egg_from_id(t_server *infos, uint32_t id)
{
  t_list	*egg;

  for (egg = infos->egg_list; egg != NULL; egg = egg->next)
    if (((t_egg *)egg->data)->id == id)
      return (egg->data);
  return (NULL);
}
