#define _GNU_SOURCE
#include <stdlib.h>
#include "network.h"

static int			get_dir(t_player *player_ejected,
					t_player *player)
{
  int32_t			i;
  static const t_dir_expulse	tab_expulse[] = {{NORTH, NORTH, 5},
						 {NORTH, EST, 3},
						 {NORTH, SOUTH, 1},
						 {NORTH, WEST, 7},
						 {EST, NORTH, 7},
						 {EST, EST, 5},
						 {EST, SOUTH, 3},
						 {EST, WEST, 1},
						 {SOUTH, NORTH, 1},
						 {SOUTH, EST, 7},
						 {SOUTH, SOUTH, 5},
						 {SOUTH, WEST, 3},
						 {WEST, NORTH, 3},
						 {WEST, EST, 1},
						 {WEST, SOUTH, 7},
						 {WEST, WEST, 5}};

  i = 0;
  while (tab_expulse[i].kicker != player->dir
	 && tab_expulse[i].kicked != player_ejected->dir)
    ++i;
  return (tab_expulse[i].value);
}

static int		move_player(t_server *infos UNUSED,
				    t_player *player_ejected UNUSED,
				    t_player *player UNUSED)
{
  char			*msg;
  static t_pos		tab[4] = {{0, -1}, {1, 0},
  				  {0, 1}, {-1, 0}};

  --infos->map[player_ejected->pos.x
	       + player_ejected->pos.y * infos->world_width].nb_player;
  player_ejected->pos.x = (player_ejected->pos.x + tab[player->dir - 1].x
			   + infos->world_width) % infos->world_width;
  player_ejected->pos.y = (player_ejected->pos.y + tab[player->dir - 1].y
			   + infos->world_height) % infos->world_height;
  ++infos->map[player_ejected->pos.x
	       + player_ejected->pos.y * infos->world_width].nb_player;
  check_incantation(player_ejected);
  graphic_cmd_send(infos, graphic_cmd_action_ppo(infos, player_ejected));
  if (asprintf(&msg, "deplacement: %d\n",
	       get_dir(player_ejected, player)) == -1)
    return (FAILURE);
  send_to_player(player, msg);
  return (SUCCESS);
}

char	*mail_handle_eject(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  t_list	*list;
  t_player	*player;
  char		*ret;

  check_incantation(msg->from);
  if ((ret = strdup(CMD_OK)) == NULL)
    return (strdup(CMD_KO));
  list = infos->network.client;
  graphic_cmd_send(infos, graphic_cmd_action_pex(infos, msg->from));
  while (list != NULL)
    {
      player = (t_player *)list->data;
      if (player != msg->from
	  && player->pos.x == msg->from->pos.x
	  && player->pos.y == msg->from->pos.y)
	{
	  if (move_player(infos, player, msg->from) == FAILURE)
	    {
	      free(ret);
	      return (NULL);
	    }
	}
      list = list->next;
    }
  return (ret);
}
