#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network_graphic.h"

char		*graphic_cmd_handle_tna(t_server *infos, t_mail *msg UNUSED)
{
  uint32_t	i;
  char		*str;
  char		*str_free;

  str = NULL;
  for (i = 0; i < infos->nb_teams; ++i)
    {
      str_free = str;
      if (asprintf(&str, "%stna %s\n",
		   str == NULL ? "" :
		   str, infos->teams_names[i]) < 0)
	{
	  free(str_free);
	  return (NULL);
	}
      free(str_free);
    }
  return (str);
}
