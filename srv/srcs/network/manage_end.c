#include <stdlib.h>
#include "network.h"

void	manage_end(t_server *infos)
{
  if (infos->winner == NULL)
    return ;
  graphic_cmd_send(infos, graphic_cmd_action_seg(infos,
						 infos->winner->team_name));
  free_infos(infos);
  exit(0);
}
