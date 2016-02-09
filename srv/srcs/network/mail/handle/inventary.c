#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#include "network.h"

static char		g_arg[7][16] = {{"nourriture"},
					{"linemate"},
					{"deraumere"},
					{"sibur"},
					{"mendiane"},
					{"phiras"},
					{"thystame"}};

char	*mail_handle_inventary(t_server *infos UNUSED, t_mail *msg)
{
  char	*ret;

  check_incantation(msg->from);
  if (asprintf(&ret, "{nourriture %d,linemate %d,deraumere %d,sibur %d,\
mendiane %d,phiras %d,thystame %d}\n", msg->from->item[0], msg->from->item[1],
	       msg->from->item[2], msg->from->item[3], msg->from->item[4],
	       msg->from->item[5], msg->from->item[6]) == -1)
    return (NULL);
  return (ret);
}

static void	take_to_graphic(t_server *infos, t_mail *msg, int i)
{
  ++msg->from->item[i];
  graphic_cmd_send(infos, graphic_cmd_action_pgt(infos, msg->from, i));
  graphic_cmd_send(infos, graphic_cmd_action_pin(infos, msg->from));
  graphic_cmd_send(infos, graphic_cmd_action_bct
		   (infos, msg->from->pos.x * msg->from->pos.x
		    + msg->from->pos.y * infos->world_width, msg->from->pos.x,
		    msg->from->pos.y));
}

char		*mail_handle_take(t_server *infos, t_mail *msg)
{
  int32_t	i;
  char		*ret;

  check_incantation(msg->from);
  if ((ret = strdup(CMD_OK)) == NULL)
    return (NULL);
  for (i = 0; i < 7; ++i)
    {
      if (strcmp(msg->data, g_arg[i]) == 0)
      	{
	  if (infos->map[msg->from->pos.x
			 + (msg->from->pos.y * infos->world_width)].item
	      [i] <= 0)
	    {
	      free(ret);
	      return (NULL);
	    }
	  --infos->map[msg->from->pos.x
		       + (msg->from->pos.y * infos->world_width)].item[i];
	  take_to_graphic(infos, msg, i);
	  return (ret);
	}
    }
  free(ret);
  return (NULL);
}

static void	drop_to_graphic(t_server *infos, t_mail *msg, int i)
{
  --msg->from->item[i];
  ++infos->map[msg->from->pos.x + (msg->from->pos.y
				   * infos->world_width)].item[i + 1];

  graphic_cmd_send(infos, graphic_cmd_action_pdr(infos, msg->from, i));
  graphic_cmd_send(infos, graphic_cmd_action_pin(infos, msg->from));
  graphic_cmd_send(infos, graphic_cmd_action_bct
  		   (infos, msg->from->pos.x * msg->from->pos.x
  		    + msg->from->pos.y * infos->world_width, msg->from->pos.x,
  		    msg->from->pos.y));
}

char		*mail_handle_drop(t_server *infos, t_mail *msg)
{
  int32_t	i;
  char		*ret;

  check_incantation(msg->from);
  if ((ret = strdup(CMD_OK)) == NULL)
    return (NULL);
  i = 0;
  while (++i < 7)
    {
      if (strcmp(msg->data, g_arg[i]) == 0)
	{
	  if (msg->from->item[i] <= 0)
	    {
	      free(ret);
	      return (NULL);
	    }
	  drop_to_graphic(infos, msg, i);
	  return (ret);
	}
    }
  free(ret);
  return (NULL);
}
