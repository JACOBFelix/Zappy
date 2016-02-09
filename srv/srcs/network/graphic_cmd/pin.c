#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network_graphic.h"

char	*graphic_cmd_action_pin(t_server *infos UNUSED,
				const t_player *player)
{
  char	*str;

  if (asprintf(&str, "pin %i %i %i %i %i %i %i %i %i %i\n",
	       player->fd, player->pos.x, player->pos.y,
	       player->item[0],
	       player->item[1],
	       player->item[2],
	       player->item[3],
	       player->item[4],
	       player->item[5],
	       player->item[6]) < 0)
    return (NULL);
  return (str);
}

char		*graphic_cmd_handle_pin(t_server *infos, t_mail *msg)
{
  t_player	*player = find_player_from_id(infos, atoi(msg->data));

  if (player == NULL)
    return (NULL);
  return (graphic_cmd_action_pin(infos, player));
}
