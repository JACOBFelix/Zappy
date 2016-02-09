#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "network.h"

static char g_name_tab[7][14] = {"nourriture",
				 "linemate",
				 "deraumere",
				 "sibur",
				 "mendiane",
				 "phiras",
				 "thystame"};

static char	*get_str_item(int count,
			      char str[])
{
  char		*tmp;
  char		*buffer;

  tmp = NULL;
  if (count > 0)
    {
      if (asprintf(&tmp, "%s", str) == -1)
	return (NULL);
    }
  while (--count > 0)
    {
      buffer = tmp;
      if (asprintf(&tmp, "%s %s", buffer, str) == -1)
	{
	  free(buffer);
	  return (NULL);
	}
      free(buffer);
    }
  return (tmp);
}

char		*item_on_case(t_server *infos,
			      t_pos pos)
{
  char		*tmp;
  char		*buffer;
  char		*stmp;
  int		i;

  tmp = get_str_item(infos->map[pos.x + pos.y * infos->world_width]
		     .nb_player, "joueur");
  for (i = 0; i < 7; ++i)
    {
      buffer = tmp;
      tmp = get_str_item(infos->map[pos.x + pos.y * infos->world_width]
			 .item[i], g_name_tab[i]);
	if (buffer != NULL && tmp != NULL)
	  {
	    if (asprintf(&stmp, "%s %s", buffer, tmp) == -1)
	      return (NULL);
	    free(buffer);
	    free(tmp);
	    tmp = stmp;
	  }
	else if (tmp == NULL)
	  tmp = buffer;
    }
  return (tmp);
}

static int	follow_handle_get_case(char **ret, char *tmp)
{
  char		*str;

  if (tmp == NULL)
    {
      if (asprintf(&str, "%s, ", *ret) == -1)
	{
	  free(*ret);
	  return (FAILURE);
	}
      free(*ret);
      *ret = str;
      return (SUCCESS);
    }
  else if (asprintf(&str, "%s, %s", *ret, tmp) == -1)
    {
      free(*ret);
      free(tmp);
      return (FAILURE);
    }
  free(*ret);
  free(tmp);
  *ret = str;
  return (SUCCESS);
}

int		handle_get_case(char **ret, char *tmp)
{
  if (*ret == NULL && tmp == NULL)
    return (asprintf(ret, ", ") == -1 ? FAILURE : SUCCESS);
  else if (*ret == NULL)
    {
      if (asprintf(ret, ", %s", tmp) == -1)
	{
	  free(tmp);
	  return (FAILURE);
	}
      free(tmp);
    return (SUCCESS);
    }
  return (follow_handle_get_case(ret, tmp));
}
