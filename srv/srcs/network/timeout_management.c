#include "network.h"

int	player_timeout_management(t_server *infos UNUSED, t_player *player)
{
  if (player->state != GRAPHIC_IS_READY
      && player->clock_last_action + 1000 * TIMEOUT_SEC
      < clock() * 1000 / CLOCKS_PER_SEC)
    {
      debug_msgf("Client %i timed out", player->fd);
      return (FAILURE);
    }
  return (SUCCESS);
}
