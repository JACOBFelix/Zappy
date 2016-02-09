#include <stdlib.h>
#include "server.h"

int32_t		get_width(t_server *infos,
			  uint32_t i,
			  uint32_t ac,
			  char **ag)
{
  if (i < ac - 1 && !is_number(ag[i + 1]))
  {
    if ((infos->world_width = (uint16_t)atoi(ag[i + 1])) == 0)
      {
	print_errorf("wring width '%s', it can't be 0", ag[i + 1]);
	return (-1);
      }
    debug_msgf("WIDTH: %u", infos->world_width);
  }
  else if (i < ac - 1)
  {
    print_errorf("wrong width '%s'", ag[i + 1]);
    return (-1);
  }
  else
  {
    print_error("missing width");
    return (-1);
  }
  return (i + 2);
}
