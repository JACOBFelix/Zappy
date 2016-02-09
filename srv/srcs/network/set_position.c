#include <stdlib.h>
#include <string.h>
#include "network.h"

static void	set_rand_pos(t_server *infos, t_player *player)
{
  player->pos.x = rand() % infos->world_width;
  player->pos.y = rand() % infos->world_height;
  player->dir = rand() % 4 + 1;
}

static t_list	*get_egg(t_server *infos UNUSED, t_player *player UNUSED)
{
  t_list	*tmp;
  t_list	*list;
  t_egg		*egg;
  t_egg		*egg_tmp;

  list = infos->egg_list;
  egg = NULL;
  tmp = NULL;
  while (list != NULL)
    {
      egg_tmp = (t_egg *)list->data;
      if (strcmp(egg_tmp->team_name, player->team_name) == 0
	  && (egg == NULL || egg_tmp->time < egg->time))
	{
	  egg = egg_tmp;
	  tmp = list;
	}
      list = list->next;
    }
  return (tmp);
}
void		set_position(t_server *infos,
			     t_player *player)
{
  t_list	*list;
  t_egg		*egg;

  set_rand_pos(infos, player);
  if ((list = get_egg(infos, player)) == NULL)
    {
      ++infos->map[player->pos.x + player->pos.y
		   * infos->world_width].nb_player;
      return ;
    }
  egg = (t_egg *)list->data;
  player->pos.x = egg->pos.x;
  player->pos.y = egg->pos.y;
  graphic_cmd_send(infos, graphic_cmd_action_eht(infos, egg));
  graphic_cmd_send(infos, graphic_cmd_action_ebo(infos, egg));
  free(egg->team_name);
  free(egg);
  remove_node(&infos->egg_list, list);
  ++infos->map[player->pos.x + player->pos.y
	       * infos->world_width].nb_player;
}
