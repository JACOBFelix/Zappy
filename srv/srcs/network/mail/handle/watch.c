#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network.h"

static void		set_point_of_line(t_pos *start,
					  t_pos *end,
					  int i,
					  t_mail *msg)
{
  static const t_pos	start_tab[] = {{-1, -1}, {1, -1}, {1, 1}, {1, 1}};
  static const t_pos	end_tab[] = {{1, -1}, {1, 1}, {-1, 1}, {1, -1}};

  start->x = start_tab[msg->from->dir - 1].x * i;
  start->y = start_tab[msg->from->dir - 1].y * i;
  end->x = end_tab[msg->from->dir - 1].x * i;
  end->y = end_tab[msg->from->dir - 1].y * i;
}

char			*watch_line(t_server *infos,
				    t_mail *msg,
				    int i,
				    char *ret)
{
  t_pos			start;
  t_pos			end;
  static const t_pos	inc[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
  t_pos			pos_tmp;

  set_point_of_line(&start, &end, i, msg);
  while (start.x != end.x || start.y != end.y)
    {
      pos_tmp.x = (msg->from->pos.x + start.x + infos->world_width)
	% infos->world_width;
      pos_tmp.y = (msg->from->pos.y + start.y + infos->world_height)
	% infos->world_height;
      if (handle_get_case(&ret, item_on_case(infos, pos_tmp)) == FAILURE)
	return (NULL);
      start.x += inc[msg->from->dir - 1].x;
      start.y += inc[msg->from->dir - 1].y;
    }
  pos_tmp.x = (msg->from->pos.x + start.x + infos->world_width)
    % infos->world_width;
  pos_tmp.y = (msg->from->pos.y + start.y + infos->world_height)
    % infos->world_height;
  if (handle_get_case(&ret, item_on_case(infos, pos_tmp)) == FAILURE)
    return (NULL);
  return (ret);
}

static char		*end_watch(t_server *infos,
				   const t_player *player,
				   char *ret)
{
  char			*tmp;

  if (asprintf(&tmp, "{ %s}\n", ret) == -1)
    {
      free(ret);
      return (NULL);
    }
  free(ret);
  graphic_cmd_send(infos, graphic_cmd_action_ppo(infos, player));
  return (tmp);
}

char			*mail_handle_watch(t_server *infos, t_mail *msg)
{
  char			*ret;
  char			*buffer;
  char			*tmp;
  int			i;
  int			j;

  check_incantation(msg->from);
  if ((ret = item_on_case(infos, msg->from->pos)) == NULL)
    return (NULL);
  for (i = 1; i < msg->from->level + 1; ++i)
    {
      if ((buffer = watch_line(infos, msg, i, NULL)) == NULL)
	{
	  free(ret);
	  return (NULL);
	}
      j = asprintf(&tmp, "%s%s", ret, buffer);
      free(ret);
      free(buffer);
      if (j == -1)
	return (NULL);
      ret = tmp;
    }
  return (end_watch(infos, msg->from, ret));
}
