#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include "network.h"

static const int	g_tab[7][7] = {{0, 1, 0, 0, 0, 0, 0},
				       {0, 1, 1, 1, 0, 0, 0},
				       {0, 2, 0, 1, 0, 2, 0},
				       {0, 1, 1, 2, 0, 1, 0},
				       {0, 1, 2, 1, 3, 0, 0},
				       {0, 1, 2, 3, 0, 1, 0},
				       {0, 2, 2, 2, 2, 2, 1}};
static const int	g_nb_player[] = {1, 2, 2, 4, 4, 6, 6};

void		remove_incantation(t_server *infos,
				   t_incantation *incantation)
{
  t_list	*list;

  list = infos->incantation_list;
  while (list != NULL)
    {
      if (list->data == incantation)
	{
	  remove_node(&infos->incantation_list, list);
	  return ;
	}
      list = list->next;
    }
}

int	can_incantation(t_server *infos, t_player *player)
{
  int	i;

  i = -1;
  if (infos->map[player->pos.x + player->pos.y * infos->world_width].nb_player
      != g_nb_player[player->level - 1])
    return (FAILURE);
  while (++i < 7)
    {
      if (infos->map[player->pos.x + player->pos.y
		     * infos->world_width].item[i]
	  != g_tab[player->level - 1][i])
	return (FAILURE);
    }
  return (SUCCESS);
}

void		init_incantation(t_server *infos,
				 t_mail *msg,
				 t_incantation *new_incantation)
{
  t_player	*player;
  t_list	*list;
  int		i;

  new_incantation->pos.x = msg->from->pos.x;
  new_incantation->pos.y = msg->from->pos.y;
  list = infos->network.client;
  new_incantation->success = 0;
  i = 0;
  while (list != NULL)
    {
      player = (t_player *)list->data;
      if (player->pos.x == new_incantation->pos.x
	  && player->pos.y == new_incantation->pos.y
	  && player->level == msg->from->level)
	{
	  send_to_player(player, strdup("elevation en cours\n"));
	  new_incantation->player[i] = player;
	  player->incantation = new_incantation;
	  ++i;
	}
      list = list->next;
    }
  new_incantation->player[i] = NULL;
}

void		create_incantation(t_server *infos, t_mail *msg)
{
  t_incantation	*new_incantation;

  if (can_incantation(infos, msg->from) == FAILURE)
    {
      msg->from->action.clock = clock() * 1000 / CLOCKS_PER_SEC
	+ 1000 / infos->exec_delay;
      return ;
    }
  if ((new_incantation = malloc(sizeof(t_incantation))) == NULL)
    return ;
  if ((new_incantation->player = malloc(sizeof(t_player *)
					* (g_nb_player[msg->from->level - 1]
					   + 1))) == NULL)
    {
      free(new_incantation);
      return ;
    }
  if (list_push_front(&infos->incantation_list, new_incantation) == FAILURE)
    {
      free(new_incantation->player);
      free(new_incantation);
      return ;
    }
  end_create_incantation(infos, msg, new_incantation);
}

void	remove_item_incantation(t_server *infos UNUSED,
				t_incantation *incantation UNUSED,
				t_player *player)
{
  int	i;

  i = 0;
  while (++i < 7)
    {
      if (infos->map[incantation->pos.x + incantation->pos.y
		     * infos->world_width].item[i] <= g_tab[player->level
							    - 1][i])
	infos->map[incantation->pos.x + incantation->pos.y *
		   infos->world_width].item[i] = 0;
      else
	infos->map[incantation->pos.x + incantation->pos.y
		   * infos->world_width].item[i]
	  -= g_tab[player->level - 1][i];
    }
}
