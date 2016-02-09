#include <poll.h>
#include "stdlib.h"
#include "network.h"
#include "display.h"

static struct pollfd	*init_poll(t_server *infos,
				   struct pollfd *fds,
				   nfds_t *nfds)
{
  t_list		*elem;
  uint32_t		size;
  uint32_t		i;

  if ((size = list_size(infos->network.client)) + 1 != *nfds)
  {
    fds = realloc(fds, sizeof(struct pollfd) * (size + 1));
    *nfds = size + 1;
  }
  for (i = 1, elem = infos->network.client; elem; elem = elem->next, i += 1)
  {
    fds[i].fd = ((t_player *)elem->data)->fd;
    fds[i].events = POLLIN;
    if (((t_player *)elem->data)->list_buffer_out != NULL)
      fds[i].events |= POLLOUT;
  }
  return (fds);
}

static int32_t	post_poll(t_server *infos, struct pollfd *fds)
{
  if (fds[0].revents & POLLIN)
  {
    add_client(infos);
  }
  else
  {
    manage_client(infos, fds);
  }
  return (SUCCESS);
}

static struct pollfd	*init_server_fd(t_server *infos)
{
  struct pollfd		*fds;

  if ((fds = (struct pollfd *)malloc(sizeof(*fds))))
  {
    fds->fd = infos->network.fd;
    fds->events = POLLIN;
  }
  else
    derror("malloc");
  return (fds);
}

static void		call_handle_for_clients(t_server *infos)
{
  t_list		*client;
  t_player		*player;
  uint32_t const	food = get_food_amount_to_remove(infos);

  client = infos->network.client;
  while (client != NULL)
    {
      player = client->data;
      client = client->next;
      if (player->state == PLAYER_IS_READY
	  && (player_timeout_management(infos, player) == FAILURE
	  || player_food_management(infos, player, food) == FAILURE))
	{
	  graphic_cmd_send(infos, graphic_cmd_action_pdi(infos, player));
	  check_dead_incantation(player);
	  close(player->fd);
	  infos->network.client = delete_client(infos, player);
	}
      else
	{
	  handle_client(infos, player);
	}
    }
}

int32_t		loop_server(t_server *infos)
{
  t_display	d;
  nfds_t	nfds;
  int		ret_poll;

  if (!infos->gui_down && init_display(&d) == -1)
    close_display(&d, 1);
  if ((infos->network.fds = init_server_fd(infos)))
  {
    nfds = 1;
    ret_poll = 0;
    infos->clock = clock() * 1000 / CLOCKS_PER_SEC;
    while (infos->network.alive)
    {
      manage_end(infos);
      manage_display(&d, infos);
      infos->network.fds = init_poll(infos, infos->network.fds, &nfds);
      if ((ret_poll = poll(infos->network.fds, nfds, 0)) > 0)
	post_poll(infos, infos->network.fds);
      else if (ret_poll < 0)
	return (derror("poll"));
      call_handle_for_clients(infos);
    }
  }
  close_display(&d, 0);
  return (SUCCESS);
}
