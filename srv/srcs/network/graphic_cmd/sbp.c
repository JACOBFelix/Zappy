#include <stdio.h>
#include "network_graphic.h"

char	*graphic_cmd_action_sbp(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  return (strdup("sbp\n"));
}
