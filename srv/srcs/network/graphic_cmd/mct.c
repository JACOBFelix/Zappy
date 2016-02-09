#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network_graphic.h"

static char		*get_content_case(t_server *infos,
					  int x,
					  int y,
					  char *prev)
{
  uint32_t const	idx = x + y * infos->world_width;
  char			*str;

  if (asprintf(&str, "%sbct %i %i %i %i %i %i %i %i %i\n",
	       prev,
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
** content of every case (bct on all)
*/
char		*graphic_cmd_handle_mct(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  char		*str;
  char		*tmp;
  uint32_t	x;
  uint32_t	y;

  str = NULL;
  for (x = 0; x < infos->world_width; ++x)
    {
      for (y = 0; y < infos->world_height; ++y)
	{
	  tmp = get_content_case(infos, x, y, (str == NULL ? "" : str));
	  free(str);
	  if (tmp == NULL)
	    {
	      debug_msgf("mct: asprintf failed");
	      return (NULL);
	    }
	  str = tmp;
	}
    }
  return (str);
}
