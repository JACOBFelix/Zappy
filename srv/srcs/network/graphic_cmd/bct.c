#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network_graphic.h"

static int	graphic_cmd_handle_bct_parse(t_server *infos,
					     t_mail *msg,
					     int *x,
					     int *y)
{
  char		*tok;

  tok = msg->data;
  *x = atoi(tok);
  if ((tok = strchr(tok, ' ')) == NULL || tok[1] == '\0')
    {
      debug_msgf("bct: invalid tok '%s'", msg->data);
      return (-1);
    }
  *y = atoi(tok + 1);
  if ((uint32_t)*x > infos->world_width
      || (uint32_t)*y > infos->world_height
      || *x < 0 || *y < 0)
    {
      debug_msgf("bct: invalid tok values %i %i", *x, *y);
      return (-1);
    }
  return (*x + *y * infos->world_width);
}

char		*graphic_cmd_action_bct(t_server *infos, int idx, int x, int y)
{
  char		*str;

  if (asprintf(&str, "bct %i %i %i %i %i %i %i %i %i\n",
	       x, y,
	       infos->map[idx].item[0],
	       infos->map[idx].item[1],
	       infos->map[idx].item[2],
	       infos->map[idx].item[3],
	       infos->map[idx].item[4],
	       infos->map[idx].item[5],
	       infos->map[idx].item[6]) < 0)
    return (NULL);
  return (str);
}

/*
** content of ONE case
*/
char		*graphic_cmd_handle_bct(t_server *infos UNUSED, t_mail *msg)
{
  int		x;
  int		y;
  int const	idx = graphic_cmd_handle_bct_parse(infos, msg, &x, &y);

  if (idx < 0)
    return (NULL);
  return (graphic_cmd_action_bct(infos, idx, x, y));
}
