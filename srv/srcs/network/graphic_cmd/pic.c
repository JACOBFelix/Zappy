#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network_graphic.h"

static char	*parse_incantation(t_incantation *incantation,
				   int i)
{
  char		*str;
  char		*tmp;

  str = NULL;
  while (incantation->player[++i] != NULL)
    {
      if (str == NULL)
	{
	  if (asprintf(&tmp, "%d", incantation->player[i]->fd) == -1)
	    return (NULL);
	  str = tmp;
	}
      else
	{
	  if (asprintf(&tmp, "%s %d", str, incantation->player[i]->fd) == -1)
	    {
	      free(str);
	      return (NULL);
	    }
	  free(str);
	  str = tmp;
	}
    }
  return (str);
}

char	*graphic_cmd_action_pic(t_server *infos UNUSED, t_mail *msg UNUSED,
				t_incantation *incantation UNUSED)
{
  char	*str;

  if ((str = parse_incantation(incantation, -1)) == NULL)
    {
      if (asprintf(&str, "pic %i %i %i %i\n",
		   msg->from->pos.x, msg->from->pos.y, msg->from->level,
		   msg->from->fd) == -1)
	return (NULL);
      return (str);
    }
  if (asprintf(&str, "pic %i %i %i %s\n",
	       msg->from->pos.x, msg->from->pos.y, msg->from->level, str) < 0)
    return (NULL);
  return (str);
}
