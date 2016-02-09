#include <stdlib.h>
#include "network.h"

void	end_create_incantation(t_server *infos,
			       t_mail *msg,
			       t_incantation *new_incantation)
{
  init_incantation(infos, msg, new_incantation);
  if (can_incantation(infos, msg->from) == FAILURE)
    new_incantation->success = 0;
  graphic_cmd_send(infos, graphic_cmd_action_pic(infos, msg,
						 new_incantation));
}

void	check_dead_incantation(t_player *player)
{
  int	i;

  if (player->incantation == NULL)
    return ;
  player->incantation->success = 1;
  i = -1;
  while (player->incantation->player[++i] != player)
    ;
  while (player->incantation->player[i] != NULL)
    {
      player->incantation->player[i] = player->incantation->player[i + 1];
      if (player->incantation->player[i] == NULL)
	break ;
      ++i;
    }
}
