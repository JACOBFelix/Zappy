#include <stdlib.h>
#include "server.h"

int32_t		get_height(t_server *infos,
			   uint32_t i,
			   uint32_t ac,
			   char **ag)
{
  if (i < ac - 1 && !is_number(ag[i + 1]))
  {
    if ((infos->world_height = (uint16_t)atoi(ag[i + 1])) == 0)
      {
	print_errorf("wrong height '%s', it can't be 0", ag[i + 1]);
	return (-1);
      };
    debug_msgf("HEIGHT: %u", infos->world_height);
  }
  else if (i < ac - 1)
  {
    print_errorf("wrong height '%s'", ag[i + 1]);
    return (-1);
  }
  else
  {
    print_error("missing height");
    return (-1);
  }
  return (i + 2);
}
