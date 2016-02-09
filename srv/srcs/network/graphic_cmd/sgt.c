#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

char	*graphic_cmd_action_sgt(t_server *infos UNUSED)
{
  char	*str;

  if (asprintf(&str, "sgt %u\n", infos->exec_delay) < 0)
    return (NULL);
  return (str);
}

/*
** send the exec_delay
*/
char	*graphic_cmd_handle_sgt(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  return (graphic_cmd_action_sgt(infos));
}
