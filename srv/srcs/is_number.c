#include <string.h>
#include "server.h"

int32_t		is_number(char *nb)
{
  uint32_t	i;
  uint32_t	len;

  for (i = 0, len = strlen(nb); i < len; i += 1)
  {
    if (nb[i] < '0' || nb[i] > '9')
      return (-1);
  }
  return (0);
}
