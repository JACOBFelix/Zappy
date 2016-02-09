#include <string.h>
#include <stdlib.h>
#include "server.h"
#include "options.h"

static int32_t	is_end_teams(char *ag)
{
  uint32_t	i;

  for (i = 0; i < g_size_options; i += 1)
  {
    if (!strncmp(g_options[i].name, ag, 2))
      return (1);
  }
  return (0);
}

static int32_t	list_to_tab(t_server *infos,
			    t_list_str *list,
			    uint32_t nb)
{
  char		**tab;
  t_list_str	*begin_list;
  uint32_t	i;

  begin_list = list;
  tab = malloc(sizeof(char *) * (nb + 1));
  memset(tab, 0, sizeof(char *) * (nb + 1));
  for (i = 0; i < nb; i += 1, list = list->next)
  {
    tab[i] = strdup(list->str);
    debug_msgf("TEAM[%u]: '%s'", i, tab[i]);
  }
  infos->teams_names = tab;
  erase_list_str(&begin_list);
  return (i);
}

int32_t		get_teams(t_server *infos,
			  uint32_t i,
			  uint32_t ac,
			  char **ag)
{
  t_list_str	*list;
  uint32_t	nb;

  (void)infos;
  list = (t_list_str *)0;
  for (i += 1; i < ac && !is_end_teams(ag[i]); i += 1)
  {
    push_str(&list, ag[i]);
  }
  nb = get_size_list_str(list);
  infos->nb_teams = nb;
  if (nb)
  {
    list_to_tab(infos, list, nb);
    return (i);
  }
  print_error("missing teams names");
  return (-1);
}
