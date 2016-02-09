#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

/*
** oeuf N pondu par joueur I sur case X Y
** enw N I X Y
*/
char	*graphic_cmd_action_enw(t_server *infos UNUSED,
				t_player *player,
				t_egg *egg)
{
  char	*str;

  if (asprintf(&str, "enw %i %i %i %i\n",
	       egg->id, player->fd,
	       player->pos.x, player->pos.y) < 0)
    return (NULL);
  return (str);
}
