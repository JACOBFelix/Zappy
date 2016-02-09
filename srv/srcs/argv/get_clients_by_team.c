#include <stdlib.h>
#include "server.h"

int32_t		get_players_by_team(t_server *infos,
				    uint32_t i,
				    uint32_t ac,
				    char **ag)
{
  if (i < ac - 1 && !is_number(ag[i + 1]))
  {
    infos->clients_by_team = (uint32_t)atoi(ag[i + 1]);
    debug_msgf("CLIENTS BY TEAM: %u", infos->clients_by_team);
  }
  else if (i < ac - 1)
  {
    print_errorf("wrong nb clients by team '%s'", ag[i + 1]);
    return (-1);
  }
  else
  {
    print_error("missing nb clients by team");
    return (-1);
  }
  return (i + 2);
}
