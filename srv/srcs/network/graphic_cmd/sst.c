#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network_graphic.h"

char		*graphic_cmd_handle_sst(t_server *infos, t_mail *msg)
{
  uint32_t	t = atoi(msg->data);

  if (t > 0)
    {
      infos->exec_delay = t;
    }
  return (graphic_cmd_handle_sgt(infos, msg));
}
