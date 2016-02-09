#include "network.h"

uint32_t		get_food_amount_to_remove(t_server *infos)
{
  clock_t const		t = clock() * 1000 / CLOCKS_PER_SEC;
  clock_t const		tdiff = t - infos->clock;
  uint32_t const	amount = tdiff ? tdiff * infos->exec_delay / 1000 : 0;

  if (amount > 0)
    {
      infos->clock = clock() * 1000 / CLOCKS_PER_SEC;
    }
  return (amount);
}

int			player_food_management(t_server *infos UNUSED,
					       t_player *player,
					       uint32_t food)
{
  if (food == 0)
    return (SUCCESS);
  player->item[0] -= food;
  if (player->item[0] <= 0)
    {
      graphic_cmd_send(infos, graphic_cmd_action_pdi(infos, player));
      debug_msgf("Player %i die from starve", player->fd);
      return (FAILURE);
    }
  return (SUCCESS);
}
