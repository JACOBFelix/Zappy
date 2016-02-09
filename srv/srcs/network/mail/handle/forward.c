#include "network.h"
#include "positions.h"

char			*mail_handle_forward(t_server *infos, t_mail *msg)
{
  char			*ret;
  static const t_pos	tpos[4] = {{0, -1},
				  {1, 0},
				  {0, 1},
				  {-1, 0}};

  check_incantation(msg->from);
  if ((ret = strdup(CMD_OK)) == NULL)
    return (NULL);
  --infos->map[msg->from->pos.x + msg->from->pos.y
	       * infos->world_width].nb_player;
  msg->from->pos.x = (msg->from->pos.x + tpos[msg->from->dir - 1].x
		      + infos->world_width) % infos->world_width;
  msg->from->pos.y = (msg->from->pos.y + tpos[msg->from->dir - 1].y
		      + infos->world_height) % infos->world_height;
  ++infos->map[msg->from->pos.x +  msg->from->pos.y *
	       infos->world_width].nb_player;
  graphic_cmd_send(infos, graphic_cmd_action_ppo(infos, msg->from));
  return (ret);
}
