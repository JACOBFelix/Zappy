#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

char	*graphic_cmd_action_smg(t_server *infos UNUSED, char *what)
{
  char	*str;

  if (asprintf(&str, "smg %s\n", what) < 0)
    return (NULL);
  return (str);
}
