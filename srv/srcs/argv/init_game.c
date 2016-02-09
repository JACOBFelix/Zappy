#include <string.h>
#include <stdlib.h>
#include "server.h"

static uint32_t	alloc_teams(t_server *infos)
{
  uint32_t	*tmp;
  uint32_t	size;

  size = infos->nb_teams;
  tmp = malloc(sizeof(size_t) * size);
  if (tmp)
  {
    memset(tmp, 0, sizeof(size_t) * size);
  }
  infos->nb_players_team = tmp;
  return ((tmp) ? (SUCCESS) : (FAILURE));
}

uint32_t	init_game(t_server *infos)
{
  if (!create_map(infos))
    return (FAILURE);
  if (!alloc_teams(infos))
    return (FAILURE);
  if (!init_network(infos))
    return (FAILURE);
  return (SUCCESS);
}
