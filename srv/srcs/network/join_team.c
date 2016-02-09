#include <stdio.h>
#include <poll.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "network_graphic.h"

static void	delete_newline(char *s)
{
  uint32_t	i;

  if (!s)
    return ;
  for (i = 0; s[i]; i += 1)
  {
    if (s[i] == '\n' && !s[i + 1])
      s[i] = 0;
    if (s[i] == '\r' && s[i + 1] == '\n' && !s[i + 2])
      s[i] = 0;
  }
}

static void	send_remaining_players(t_server *infos,
				       t_player *player,
				       uint32_t i)
{
  uint32_t	nb;
  char		buffer[64];

  nb = infos->clients_by_team - infos->nb_players_team[i] + 1;
  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer) - 1, "%u\n", nb);
  send_to_player(player, buffer);
}

static void	send_world_size(t_server *infos,
				t_player *player)
{
  char		buffer[64];

  memset(buffer, 0, sizeof(buffer));
  snprintf(buffer, sizeof(buffer),
	   "%u %u\n", infos->world_width, infos->world_height);
  send_to_player(player, buffer);
}

static void	add_to_team(t_server *infos,
			    t_player *player,
			    uint32_t i)
{
  player->team_name = strdup(infos->teams_names[i]);
  infos->nb_players_team[i] += 1;
  list_pop_back(&(player->list_buffer_in));
  send_remaining_players(infos, player, i);
  set_position(infos, player);
  debug_msgf("player %d joined team '%s' at %i:%i",
	     player->fd, player->team_name,
	     player->pos.x, player->pos.y);
  graphic_cmd_send(infos, graphic_cmd_action_pnw(infos, player));
}

int		join_team(t_server *infos,
			 t_player *player)
{
  uint32_t	i;

  if (read_client(infos, player) == FAILURE || player->list_buffer_in == NULL)
    return (FAILURE);
  delete_newline(player->list_buffer_in->data);
  for (i = 0; infos->teams_names[i]; i += 1)
  {
    if (!strcmp(infos->teams_names[i], player->list_buffer_in->data)
	&& infos->nb_players_team[i] < infos->clients_by_team)
     {
       add_to_team(infos, player, i);
       send_world_size(infos, player);
       player->state = PLAYER_IS_READY;
       return (SUCCESS);
     }
  }
  if (strcmp(player->list_buffer_in->data, "GRAPHIC") == 0)
    return (graphic_add_client(infos, player));
  else
  {
    debug_msgf("client %d, team '%s' undefined", player->fd,
	       player->list_buffer_in->data);
  }
  return (SUCCESS);
}
