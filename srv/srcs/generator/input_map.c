#include <string.h>
#include <stdlib.h>
#include "server.h"

t_egg		*create_egg(t_server *infos, t_player *player)
{
  t_egg		*new_egg;

  if ((new_egg = malloc(sizeof(t_egg))) == NULL)
    return (NULL);
  new_egg->pos.x = player->pos.x;
  new_egg->pos.y = player->pos.y;
  new_egg->team_name = player->team_name;
  new_egg->time = clock() * 1000 / CLOCKS_PER_SEC + infos->exec_delay * 600;
  return (new_egg);
}

t_player	*create_new_player(t_server *infos UNUSED, t_egg *egg)
{
  t_player	*new_player;

  if ((new_player = malloc(sizeof(t_player))) == NULL)
    return (NULL);
  memset(new_player, 0, sizeof(t_player));
  new_player->pos.x = egg->pos.x;
  new_player->pos.y = egg->pos.y;
  new_player->team_name = egg->team_name;
  return (new_player);
}

void			create_rand_special_item(t_server *infos, int id)
{
  infos->map[rand() % (infos->world_width * infos->world_height)].item[id]
    += 1;
}

void			create_rand_diff_item(t_server *infos UNUSED)
{
  int			i;
  static int const	item_tab_generator[] = {90,
						70,
						60,
						50,
						40,
						30,
						20};

  i = -1;
  while (++i < 7)
    if (rand() % 100 < item_tab_generator[i])
      create_rand_special_item(infos, i);
}
