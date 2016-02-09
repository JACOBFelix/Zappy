#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

char	*graphic_cmd_action_pie(t_server *infos UNUSED,
				t_player *player UNUSED,
				int flag UNUSED)
{
  char	*str;

  if (asprintf(&str, "pie %i %i %i\n",
	       player->pos.x,
	       player->pos.y,
	       flag) < 0)
    return (NULL);
  return (str);
}
