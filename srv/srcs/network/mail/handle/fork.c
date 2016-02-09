#include <stdlib.h>
#include "network.h"

static void	copy_position(t_pos *to, t_pos *from)
{
  to->x = from->x;
  to->y = from->y;
}

static char		*new_egg(t_mail *msg, t_egg **egg)
{
  char			*ret;
  static uint32_t	id = 1;

  if ((*egg = malloc(sizeof(t_egg))) == NULL)
    return (NULL);
  if (((*egg)->team_name = strdup(msg->from->team_name)) == NULL)
    {
      free(*egg);
      return (NULL);
    }
  if ((ret = strdup(CMD_OK)) == NULL)
    {
      free((*egg)->team_name);
      free(*egg);
      return (NULL);
    }
  copy_position(&(*egg)->pos, &msg->from->pos);
  (*egg)->time = clock();
  (*egg)->id = id;
  id++;
  return (ret);
}

char	*mail_handle_fork(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  char	*ret;
  t_egg	*egg;

  check_incantation(msg->from);
  if ((ret = new_egg(msg, &egg)) == NULL)
    return (NULL);
  if (list_push_front(&infos->egg_list, egg) == FAILURE)
    {
      free(ret);
      free(egg->team_name);
      free(egg);
      return (NULL);
    }
  graphic_cmd_send(infos, graphic_cmd_action_enw(infos, msg->from, egg));
  return (ret);
}
