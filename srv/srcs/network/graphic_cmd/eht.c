#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

char		*graphic_cmd_action_eht(t_server *infos UNUSED, t_egg *egg)
{
  char		*str;

  if (asprintf(&str, "eht %u\n", egg->id) < 0)
    return (NULL);
  return (str);
}
