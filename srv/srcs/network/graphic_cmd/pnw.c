#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network_graphic.h"

int	gcmd_pnw_find_cli(void *a, void *b)
{
  return (((t_player *)b)->fd == (long)a ? SUCCESS : FAILURE);
}

char	*graphic_cmd_action_pnw(t_server *infos UNUSED, t_player *cli)
{
  char	*str;

  if (asprintf(&str, "pnw %i %i %i %i %i %s\n",
	       cli->fd, cli->pos.x, cli->pos.y,
	       cli->dir, cli->level, cli->team_name) == -1)
    {
      return (NULL);
    }
  return (str);
}

char		*graphic_cmd_handle_pnw(t_server *infos UNUSED, t_mail *msg)
{
  int const	idx = atoi(msg->data);
  t_list const	*list = list_search_elem(infos->network.client,
					 (void *)(long)idx,
					 &gcmd_pnw_find_cli);

  if (list == NULL)
    return (NULL);
  return (graphic_cmd_action_pnw(infos, list->data));
}
