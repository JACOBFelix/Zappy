#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "network.h"

float	distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2)
{
  return (sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2))));
}

uint32_t		index_max_float(float const *tab, uint32_t size)
{
  register uint32_t	i;
  float			max;
  uint32_t		i_max;

  if (size == 0)
    return (0);
  max = tab[0];
  i_max = 0;
  for (i = 1; i < size; ++i)
    {
      if (tab[i] > max)
	{
	  i_max = i + 1;
	  max = tab[i];
	}
    }
  return (i_max);
}

t_pos		action_broadcast_find_nearest_position(t_server *infos,
						       t_pos *player,
						       t_pos *target)
{
  t_pos const	t[5] = {{target->x, target->y},
			{target->x + infos->world_height, target->y},
			{target->x, target->y + infos->world_width},
			{target->x - infos->world_height, target->y},
			{target->x, target->y - infos->world_width} };
  float const	d[5] = { distance(t[0].x, t[0].y, player->x, player->y),
			 distance(t[1].x, t[1].y, player->x, player->y),
			 distance(t[2].x, t[2].y, player->x, player->y),
			 distance(t[3].x, t[3].y, player->x, player->y),
			 distance(t[4].x, t[4].y, player->x, player->y) };

  return (t[index_max_float(d, 5)]);
}

uint32_t		action_broadcast_find_angle(t_pos const *player,
						    t_pos const *target)
{
  float const		a = target->x - player->x;
  float const		o = target->y - player->y;
  float const		angle = atan2(a, o);
  float const		angle2 = (angle >= 0.0) ?
    (angle) : (angle + 2.0 * M_PI);
  float const		angle3 = angle2 * 4.0 / M_PI;
  uint32_t const	i = (int32_t)(angle3) + 1;

  if ((int)a == 0 && (int)o == 0)
    return (0);
  return (i);
}

/*
** For each player on the map, calculate the neaest position
** with the msg->player.
**
** Then it will send a message to every player with the good value of orient
*/
char		*mail_handle_broadcast(t_server *infos, t_mail *msg)
{
  t_list	*client;
  t_player	*player;
  char		*str;
  uint32_t	dir;

  check_incantation(msg->from);
  client = infos->network.client;
  while (client != NULL)
    {
      player = (t_player *)client->data;
      if (player->state == PLAYER_IS_READY)
	{
	  dir = (PLAYERS_POS_EQ(player, msg->from) ? 0
		 : action_broadcast_find_angle(&msg->from->pos, &player->pos)
		 + msg->from->dir) % 9;
	  if (asprintf(&str, "message %u,%s\n", dir, msg->data) == -1)
	    return (NULL);
	  send_to_player(player, str);
	  free(str);
	}
      client = client->next;
    }
  graphic_cmd_send(infos, graphic_cmd_action_pbc(infos,
						 msg->from, msg->data));
  return (strdup(CMD_OK));
}
