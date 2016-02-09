#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include "network.h"

void		send_incantation_graphic(t_server *infos,
					 t_player *player,
					 int flag)
{
  graphic_cmd_send(infos, graphic_cmd_action_pie(infos, player, flag));
  graphic_cmd_send(infos, graphic_cmd_action_plv(infos, player));
  graphic_cmd_send(infos, graphic_cmd_action_bct(infos,
						 player->pos.x + player->pos.y
						 * infos->world_width,
						 player->pos.x,
						 player->pos.y));
}

static void	free_incantation(t_server *infos, t_incantation *incantation)
{
  t_list	*list;
  int		i;

  i = -1;
  while (incantation->player[++i] != NULL)
    incantation->player[i]->incantation = NULL;
  list = infos->incantation_list;
  while (list != NULL)
    {
      if (list->data == incantation)
	{
	  free(incantation->player);
	  list_del_elem(&infos->incantation_list, list);
	  return ;
	}
      list = list->next;
    }
}

static void	incantation_do_level_up(t_incantation *incantation UNUSED)
{
  int		i;

  i = -1;
  while (incantation->player[++i] != NULL)
    incantation->player[i]->level += 1;
}

static void	transmit_message(t_server *infos UNUSED,
				 t_incantation *incantation UNUSED,
				 t_player *sender UNUSED,
				 char *msg)
{
  int		i;

  i = -1;
  while (incantation->player[++i] != NULL)
    if (incantation->player[i] != sender)
      {
	if (incantation->player[i]->level == 7)
	  infos->winner = incantation->player[i];
	send_to_player(incantation->player[i], strdup(msg));
      }
  send_incantation_graphic(infos, sender, incantation->success);
  free_incantation(infos, incantation);
}

char		*mail_handle_incantation(t_server *infos UNUSED, t_mail *msg)
{
  char		*transmited;

  if (msg->from->incantation == NULL)
    return (NULL);
  if (asprintf(&transmited, "Niveau actuel: %d\n", msg->from->level) == -1)
    {
      free_incantation(infos, msg->from->incantation);
      return (NULL);
    }
  if (can_incantation(infos, msg->from) == FAILURE)
    msg->from->incantation->success = 1;
  remove_item_incantation(infos, msg->from->incantation, msg->from);
  if (msg->from->incantation->success == 0)
    {
      transmited[strlen(transmited)- 2] += 1;
      incantation_do_level_up(msg->from->incantation);
    }
  transmit_message(infos, msg->from->incantation, msg->from, transmited);
  if (msg->from->level == 7)
    infos->winner = msg->from;
  return (transmited);
}
