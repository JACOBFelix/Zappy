#define _GNU_SOURCE
#include <stdio.h>
#include "network_graphic.h"

char	*graphic_cmd_action_seg(t_server *infos UNUSED,
				char *winner_team_name)
{
  char	*str;

  if (winner_team_name == NULL)
    {
      if (asprintf(&str, "seg ''\n") < 0)
	return (NULL);
      return (str);
    }
  if (asprintf(&str, "seg %s\n", winner_team_name) < 0)
    return (NULL);
  return (str);
}
