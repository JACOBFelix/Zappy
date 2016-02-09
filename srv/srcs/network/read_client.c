#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "network.h"

uint32_t	compare_client(t_player *c1, t_player *c2)
{
  return ((c1 == c2) ? (SUCCESS) : (FAILURE));
}

void		*delete_client(t_server *infos, t_player *del)
{
  t_list	*elem;
  t_list	*begin;
  int		idx;
  t_list	*list;

  --infos->map[del->pos.x + del->pos.y * infos->world_width].nb_player;
  list = infos->network.client;
  if ((idx = find_team_from_name(infos, del->team_name)) != -1)
    infos->nb_players_team[idx]--;
  free(del->team_name);
  while (del->list_buffer_in != NULL)
    list_pop_front(&del->list_buffer_in);
  while (del->list_buffer_out != NULL)
    list_pop_front(&del->list_buffer_out);
  if (infos->display_client == del)
    infos->display_client = NULL;
  elem = list_search_elem(list, del, (int (*)(void *, void *))compare_client);
  begin = list_del_elem(&list, elem);
  return (begin);
}

static void	push_message(t_player *client, char *buffer)
{
  char		*buf;

  if (list_size(client->list_buffer_in) < 10)
  {
    if ((buf = strdup(buffer)))
    {
      list_push_front(&(client->list_buffer_in), buf);
    }
    else
    {
      derror("strdup");
    }
  }
  else
  {
    debug_msgf("player %d: 10 messages in queue. new message ignored",
	       client->fd);
  }
}

int32_t		read_client(t_server *infos, t_player *client)
{
  static char	buffer[4096];
  int		len;
  char		*sub_buffer;
  char		*save_buffer;
  char		*token;

  memset(buffer, 0, sizeof(buffer));
  if ((len = read(client->fd, buffer, sizeof(buffer) - 1)) <= 0)
    {
      debug_msgf("Client disconnect fd(%d)", client->fd);
      infos->network.client = delete_client(infos, client);
      return (FAILURE);
    }
  else
    {
      debug_msgf("Message from fd(%d): '%s'", client->fd, buffer);
      client->clock_last_action = clock() * 1000 / CLOCKS_PER_SEC;
      for (sub_buffer = buffer;
	   (token = strtok_r(sub_buffer, "\n", &save_buffer)) != NULL;
	   sub_buffer = NULL)
	{
	  push_message(client, token);
	}
    }
  return (SUCCESS);
}
