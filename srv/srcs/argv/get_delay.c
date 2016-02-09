#include <stdlib.h>
#include "server.h"

int32_t		get_delay(t_server *infos,
			  uint32_t i,
			  uint32_t ac,
			  char **ag)
{
  if (i < ac - 1 && !is_number(ag[i + 1]))
  {
    if ((infos->exec_delay = (uint32_t)atoi(ag[i + 1])) == 0)
      {
	print_errorf("Wrong delay '%s', it can't be 0", ag[i + 1]);
	return (-1);
      }
    debug_msgf("DELAY: %u", infos->exec_delay);
  }
  else if (i < ac - 1)
  {
    print_errorf("wrong delay '%s'", ag[i + 1]);
    return (-1);
  }
  else
  {
    print_error("missing delay");
    return (-1);
  }
  return (i + 2);
}
