#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network_graphic.h"

char	*graphic_cmd_action_plv(t_server *infos UNUSED,
				const t_player *player)
{
  char	*str;

  if (asprintf(&str, "plv %i %i\n",
	       player->fd, player->level) == -1)
    return (NULL);
  return (str);
}

/*
** player level
*/
char			*graphic_cmd_handle_plv(t_server *infos UNUSED,
						t_mail *msg UNUSED)
{
  int const		id = atoi(msg->data);
  t_player const	*player = find_player_from_id(infos, id);

  if (player == NULL)
    return (NULL);
  return (graphic_cmd_action_plv(infos, player));
}
