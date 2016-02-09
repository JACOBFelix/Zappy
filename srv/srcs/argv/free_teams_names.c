#include <stdlib.h>
#include "server.h"
#include "network.h"

static void	free_clients_team_name(t_server *infos)
{
  t_list	*client;

  for (client = infos->network.client; client != NULL; client = client->next)
    {
      free(((t_player *)client->data)->team_name);
    }
}

static void	free_clients(t_server *infos)
{
  while (infos->network.client != NULL)
    infos->network.client = delete_client(infos, infos->network.client->data);
}

static void	free_eggs(t_server *infos)
{
  t_list	*list;

  while (infos->egg_list != NULL)
    {
      list = infos->egg_list;
      free(((t_egg *)infos->egg_list->data)->team_name);
      infos->egg_list = infos->egg_list->next;
      free(list->data);
      free(list);
    }
}

static void	free_incantation(t_server *infos)
{
  t_incantation	*incantation;

  while (infos->incantation_list != NULL)
    {
      incantation = (t_incantation *)infos->incantation_list->data;
      free(incantation->player);
      list_pop_front(&infos->incantation_list);
    }
  infos->incantation_list = NULL;
}

void		free_infos(t_server *infos)
{
  uint32_t	i;

  free_clients(infos);
  free_eggs(infos);
  free_clients_team_name(infos);
  free_incantation(infos);
  if (infos->teams_names != NULL)
  {
    i = 0;
    while (infos->teams_names[i] != NULL)
      {
	free(infos->teams_names[i]);
	++i;
      }
    free(infos->teams_names);
    infos->teams_names = NULL;
  }
  free(infos->map);
  infos->map = NULL;
  free(infos->nb_players_team);
  infos->nb_players_team = NULL;
  free(infos->network.local_ip);
  infos->network.local_ip = NULL;
  free(infos->network.fds);
  infos->network.fds = NULL;
}
