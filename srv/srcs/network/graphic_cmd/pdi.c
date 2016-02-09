#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

/*
** starve death
*/
char	*graphic_cmd_action_pdi(t_server *infos UNUSED, t_player *cli)
{
  char	*str;

  if (asprintf(&str, "pdi %i\n", cli->fd) == -1)
    return (NULL);
  return (str);
}
