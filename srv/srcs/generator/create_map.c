#include <string.h>
#include <stdlib.h>
#include "server.h"

static void	generat_fix(t_server *infos)
{
  int32_t	i;

  i = 99;
  while (--i != 0)
    create_rand_special_item(infos, 0);
  i = 77;
  while (--i != 0)
    create_rand_special_item(infos, 1);
  i = 66;
  while (--i != 0)
    create_rand_special_item(infos, 2);
  i = 55;
  while (--i != 0)
    create_rand_special_item(infos, 3);
  i = 44;
  while (--i != 0)
    create_rand_special_item(infos, 4);
  i = 33;
  while (--i != 0)
    create_rand_special_item(infos, 5);
  i = 22;
  while (--i != 0)
    create_rand_special_item(infos, 6);
}

int32_t		create_map(t_server *infos)
{
  int32_t	i;

  if ((infos->map = malloc(sizeof(t_map) * infos->world_width
			   * infos->world_height)) == NULL)
    return (FAILURE);
  memset(infos->map, 0, sizeof(t_map)
	 * infos->world_width * infos->world_height);
  i = infos->world_width * infos->world_height;
  if (i < 240)
    generat_fix(infos);
  else
    while (--i > -1)
      create_rand_diff_item(infos);
  return (SUCCESS);
}
