#include <stdlib.h>
#include "network.h"

void	check_incantation(t_player *player)
{
  if (player->incantation != NULL)
    player->incantation->success = 1;
}
