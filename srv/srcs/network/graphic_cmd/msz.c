#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

/*
** map size
*/
char	*graphic_cmd_handle_msz(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  char	*str;

  if (asprintf(&str, "msz %u %u\n",
	       infos->world_width, infos->world_height) < 0)
    return (NULL);
  return (str);
}
