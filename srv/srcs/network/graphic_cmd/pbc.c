#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

char	*graphic_cmd_action_pbc(t_server *infos UNUSED,
				t_player *cli,
				char *what)
{
  char	*str;

  if (asprintf(&str, "pbc %i %s\n", cli->fd, what) == -1)
    return (NULL);
  return (str);
}
