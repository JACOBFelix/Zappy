#include <stdlib.h>
#include "server.h"

int32_t		get_port(t_server *infos,
			 uint32_t i,
			 uint32_t ac,
			 char **ag)
{
  if (i < ac - 1 && !is_number(ag[i + 1]))
  {
    infos->nb_port = (uint16_t)atoi(ag[i + 1]);
    debug_msgf("PORT: %u", infos->nb_port);
  }
  else if (i < ac - 1)
  {
    print_errorf("wrong port number '%s'", ag[i + 1]);
    return (-1);
  }
  else
  {
    print_error("missing port number");
    return (-1);
  }
  return (i + 2);
}
