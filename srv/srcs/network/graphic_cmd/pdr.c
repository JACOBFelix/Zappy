#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

char	*graphic_cmd_action_pdr(t_server *infos UNUSED,
				t_player *cli,
				uint8_t rid)
{
  char	*str;

  if (asprintf(&str, "pdr %i %i\n", cli->fd, rid) == -1)
    return (NULL);
  return (str);
}
