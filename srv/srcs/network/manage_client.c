#include <stdio.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "network_graphic.h"

static t_player	*find_client(t_list *list,
			     struct pollfd *fds,
			     uint8_t *read)
{
  uint32_t	i;

  for (i = 1; list; list = list->next, i += 1)
  {
    if (fds[i].revents & POLLIN || fds[i].revents & POLLOUT)
    {
      *read = (fds[i].revents & POLLIN) ? (1) : (0);
      return (list->data);
    }
  }
  return ((t_player *)0);
}

static int	monitor_client(t_server *infos,
			       t_player *client,
			       uint8_t read)
{
  if (read)
    read_client(infos, client);
  else
    write_client(client);
  return (SUCCESS);
}

/*
** - if no action has to be done
**   - PARSE the last input buffer (queue push front pop back)
**   - REMOVE the last input buffer
** - else if an action has to be done
**   - on graphic and player (action may diff between the two types)
**     - EXECUTE the action, place the result in the client buffer_out (malloc)
**     - REMOVE the action from the client (=NULL), and free mail.data & mail
** - else MONITOR (read/write)
*/
int		handle_client(t_server *infos,
		      t_player *client)
{
  char		*str;

  if (client->action.handler != NULL)
    {
      if (client->action.clock > clock() * 1000 / CLOCKS_PER_SEC)
	return (SUCCESS);
      str = (*client->action.handler)(infos, client->action.mail);
      send_to_player(client, str);
      free(str);
      client->action.handler = NULL;
      free(client->action.mail->data);
      free(client->action.mail);
    }
  else if (client->list_buffer_in != NULL)
    {
      debug_msgf("Input Buffer found. Parse it");
      str = list_get_back(client->list_buffer_in)->data;
      if (client->state == PLAYER_IS_READY)
	mail_recv(infos, client, str);
      else if (client->state == GRAPHIC_IS_READY)
	graphic_cmd_recv(infos, client, str);
      list_pop_back(&client->list_buffer_in);
    }
  return (SUCCESS);
}

int32_t		manage_client(t_server *infos,
			      struct pollfd *fds)
{
  t_player	*client;
  uint8_t	read;

  client = find_client(infos->network.client, fds, &read);
  if (client)
  {
    if (client->state < PLAYER_IS_READY && read)
    {
      return (join_team(infos, client));
    }
    else
    {
      monitor_client(infos, client, read);
    }
  }
  return (SUCCESS);
}
