#include <stdint.h>
#include <string.h>
#include "server.h"

const t_options	g_options[] =
{
  { "-p", get_port, PORT_DONE },
  { "-x", get_width, WIDTH_DONE },
  { "-y", get_height, HEIGHT_DONE },
  { "-n", get_teams, TEAMS_DONE },
  { "-c", get_players_by_team, NB_CLIENT_DONE },
  { "-t", get_delay, DELAY_DONE },
  { "-g", disable_gui, GUI_DOWN },
};

const size_t	g_size_options = sizeof(g_options) / sizeof(g_options[0]);

static int32_t	is_option(char *arg)
{
  uint32_t	i;

  for (i = 0; i < g_size_options; i += 1)
  {
    if (!strcmp(g_options[i].name, arg))
      return (i);
  }
  print_errorf("unknown argument '%s'", arg);
  return (-1);
}

static void	set_default_values(t_server *infos, uint32_t done_flag)
{
  if (!(done_flag & PORT_DONE))
  {
    infos->nb_port = PORT_DEFAULT;
    debug_msgf("PORT: DEFAULT[%u]", PORT_DEFAULT);
  }
  if (!(done_flag & WIDTH_DONE))
  {
    infos->world_width = WIDTH_DEFAULT;
    debug_msgf("WIDTH: DEFAULT[%u]", WIDTH_DEFAULT);
  }
  if (!(done_flag & HEIGHT_DONE))
  {
    infos->world_height = HEIGHT_DEFAULT;
    debug_msgf("HEIGHT: DEFAULT[%u]", HEIGHT_DEFAULT);
  }
  if (!(done_flag & NB_CLIENT_DONE))
  {
    infos->clients_by_team = NB_CLIENT_DEFAULT;
    debug_msgf("CLIENTS BY TEAM: DEFAULT[%u]", NB_CLIENT_DEFAULT);
  }
  if (!(done_flag & DELAY_DONE))
  {
    infos->exec_delay = DELAY_DEFAULT;
    debug_msgf("DELAY: DEFAULT[%u]", DELAY_DEFAULT);
  }
}

uint8_t		parse_arguments(t_server *infos, uint32_t ac, char **ag)
{
  uint32_t	i;
  int32_t	option_number;
  uint32_t	done_flag;

  memset(infos, 0, sizeof(t_server));
  infos->gui_down = 1;
  option_number = 0;
  done_flag = 0;
  for (i = 1; i < ac; )
  {
    option_number = is_option(ag[i]);
    if (option_number >= 0 && g_options[option_number].fct)
    {
      i = g_options[option_number].fct(infos, i, ac, ag);
      done_flag |= g_options[option_number].flag;
    }
    else
      return (-1);
  }
  if (!(done_flag & TEAMS_DONE))
    return (usage(ag[0]));
  if (i != (uint32_t)-1)
    set_default_values(infos, done_flag);
  return (0);
}
