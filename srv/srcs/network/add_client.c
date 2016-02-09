#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "list.h"

static t_player		*new_client(int fd)
{
  t_player		*new;

  if ((new = (t_player *)malloc(sizeof(*new))))
  {
    memset(new, 0, sizeof(*new));
    new->fd = fd;
    new->clock_last_action = clock() * 1000 / CLOCKS_PER_SEC;
    new->level = 1;
    new->item[0] = DEFAULT_FOOD_AMOUNT * FOOD_HEAL_AMOUNT;
  }
  else
  {
    derror("could not alloc");
  }
  return (new);
}

void			add_client(t_server *infos)
{
  t_player		*client;
  struct sockaddr_in	a;
  size_t		size;
  int			fd;

  size = sizeof(a);
  if ((fd = accept(infos->network.fd,
		   (struct sockaddr*)&a,
		   (socklen_t*)&size)) == -1)
  {
    derror("accept");
    debug_msgf("Could not accept client, fd = %d", fd);
  }
  else if ((client = new_client(fd)))
  {
    if (list_push_front(&(infos->network.client), client) == FAILURE)
      {
	close(fd);
	free(client);
	return ;
      }
    debug_msgf("New client: fd(%d)", fd);
    send_to_player(client, "BIENVENUE\n");
  }
}
