#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

char	*graphic_cmd_action_pfk(t_server *infos UNUSED, t_player *cli)
{
  char	*str;

  if (asprintf(&str, "pfk %i\n", cli->fd) == -1)
    return (NULL);
  return (str);
}
