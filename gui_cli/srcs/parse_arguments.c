#include <string.h>
#include "display.h"

int	parse_arguments(int ac, char **av, int *fd, t_network *network)
{
  int	i;
  char	*port;
  char	*host;

  port = "4242";
  host = "127.0.0.1";
  for (i = 1; i < ac; i++)
    {
      if (!strcmp(av[i], "-h")
	  && i + 1 < ac)
	host = av[++i];
      else if (!strcmp(av[i], "-p")
	  && i + 1 < ac)
	port = av[++i];
    }
  *fd = network_init(host, port, network);
  if (*fd == -1)
    return (-1);
  return (0);
}
