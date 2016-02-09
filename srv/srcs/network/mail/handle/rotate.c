#include "network.h"

char	*mail_handle_right(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  char	*ret;

  check_incantation(msg->from);
  if ((ret = strdup(CMD_OK)) == NULL)
    return (NULL);
  ++msg->from->dir;
  if (msg->from->dir == 5)
    msg->from->dir = 1;
  graphic_cmd_send(infos, graphic_cmd_action_ppo(infos, msg->from));
  return (ret);
}

char	*mail_handle_left(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  char	*ret;

  check_incantation(msg->from);
  if ((ret = strdup(CMD_OK)) == NULL)
    return (NULL);
  --msg->from->dir;
  if (msg->from->dir == 0)
    msg->from->dir = 4;
  graphic_cmd_send(infos, graphic_cmd_action_ppo(infos, msg->from));
  return (ret);
}
