#include <stdlib.h>
#include "commands.h"

static t_commands	g_commands[] = {
  { "msz", set_map_size },
  { "bct", get_tile_content },
  { "tna", get_team_name },
  { "pnw", create_new_player },
  { "ppo", set_player_position },
  { "plv", set_player_level },
  { "pin", set_player_inventory },
  { "pex", player_expulsing },
  { "pbc", player_broadcasting },
  { "pic", player_incantating },
  { "pie", player_incantating_end },
  { "pfk", player_forking },
  { "pdr", player_dropping },
  { "pgt", player_getting },
  { "pdi", player_dying },
  { "enw", egg_new },
  { "eht", egg_hatching },
  { "ebo", egg_connecting },
  { "edi", egg_dying },
  { "sgt", set_game_time },
  { "seg", game_over },
  { "smg", server_message },
  { "suc", server_unknown_command },
  { "sbp", server_bad_parameter },
  { NULL, NULL }
};

static int	size_of_word(char const *const s, char const *const sep)
{
  register int	i;

  for (i = 0; s[i] && !strchr(sep, s[i]); ++i);
  return (i);
}

static int		count_words(char const *const s, char const *const sep)
{
  register unsigned int	i;
  int			count;

  for (i = count = 0; i < strlen(s); i += size_of_word(s + i, sep), ++count)
    while (i < strlen(s) && strchr(sep, s[i]))
      ++i;
  return (count);
}

/*
** string will be modified
*/
char		**str_to_wordtab(char *const s, char const *const sep)
{
  char		**tab;
  int const	words = count_words(s, sep);
  int		i;
  int		j;

  if (!(tab = malloc((sizeof(char *) * (1 + words)))))
    return (NULL);
  memset(tab, 0, sizeof(char *) * (1 + words));
  i = -1;
  j = -1;
  while (s[++i])
    {
      if (!i || ((s[i - 1] == 0 || strchr(sep, s[i - 1]))
		 && !strchr(sep, s[i]))) {
	tab[++j] = s + i;
      }
      else if (strchr(sep, s[i]))
	s[i] = 0;
    }
  return (tab);
}

int	parse_command(t_display *d, char *const str)
{
  char	**tab;
  int	i;

  if (!strcmp(str, "BIENVENUE"))
    return (0);
  tab = str_to_wordtab(str, " ");
  if (tab == NULL)
    {
      printf("Fatal error: malloc failed\n");
      return (-1);
    }
  i = 0;
  while (g_commands[i].cmd)
    {
      if (strcmp(g_commands[i].cmd, tab[0]) == 0)
	return (g_commands[i].fun(d, tab));
      i++;
    }
  return (0);
}
