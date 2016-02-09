#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network_graphic.h"

char			*graphic_cmd_action_ppo(t_server *infos UNUSED,
						const t_player *player)
{
  char			*str;

  if (asprintf(&str, "ppo %i %i %i %i\n", player->fd,
	       player->pos.x,
	       player->pos.y,
	       player->dir) < 0)
    return (NULL);
  return (str);
}

/*
** the player position
*/
char			*graphic_cmd_handle_ppo(t_server *infos UNUSED,
						t_mail *msg UNUSED)
{
  int const		id = atoi(msg->data);
  t_player const	*player = find_player_from_id(infos, id);

  if (player == NULL)
    return (NULL);
  return (graphic_cmd_action_ppo(infos, player));
}
