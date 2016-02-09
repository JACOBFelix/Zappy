#define _GNU_SOURCE
#include <stdio.h>
#include "network.h"
#include "network_graphic.h"

void		graphic_init_connection(t_server *infos, t_player *client)
{
  t_list	*list;
  t_player	*player;
  char		*str;

  debug_msgf("GRAPHIC CLIENT connected %i", client->fd);
  infos->display_client = client;
  client->state = GRAPHIC_IS_READY;
  list_push_front(&client->list_buffer_in, strdup("msz\n"));
  list_push_front(&client->list_buffer_in, strdup("sgt\n"));
  list_push_front(&client->list_buffer_in, strdup("mct\n"));
  list_push_front(&client->list_buffer_in, strdup("tna\n"));
  for (list = infos->network.client; list != NULL; list = list->next)
    {
      player = list->data;
      if (player->state == PLAYER_IS_READY)
	{
	  if (asprintf(&str, "pnw %i\n", player->fd) != -1)
	    list_push_front(&client->list_buffer_in, str);
	}
    }
}

int		graphic_add_client(t_server *infos, t_player *client)
{
  if (infos->display_client != NULL)
    {
      debug_msgf("GUI already connected %i", infos->display_client->fd);
      return (FAILURE);
    }
  list_pop_back(&(client->list_buffer_in));
  graphic_init_connection(infos, client);
  return (SUCCESS);
}
