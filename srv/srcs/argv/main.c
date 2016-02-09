#include <string.h>
#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include "server.h"
#include "network.h"

#ifndef TEST_MODE

static void		manage_sigint(t_server *ptr)
{
  static t_server	*server = (t_server *)0;

  if (ptr)
  {
    server = ptr;
  }
  else
  {
    if (server)
      free_infos(server);
    exit(0);
  }
}

static void	handler_sigint(int unused __attribute__ ((unused)))
{
  manage_sigint((t_server *)0);
}

static int	sub_main(t_server *infos,
			 int const ac UNUSED,
			 char const *const ag[] UNUSED)
{
  if (parse_arguments(infos, ac, (char **)ag))
    return (-1);
  if (init_game(infos))
    return (-1);
  if (loop_server(infos))
    return (-1);
  return (0);
}

int		main(int const ac UNUSED,
		     char const *const ag[] UNUSED)
{
  t_server	infos;
  int		ret;

  srand(time(NULL));
  memset(&infos, 0, sizeof(t_server));
  manage_sigint(&infos);
  signal(SIGINT, handler_sigint);
  ret = sub_main(&infos, ac, ag);
  free_infos(&infos);
  return (ret);
}

#endif
