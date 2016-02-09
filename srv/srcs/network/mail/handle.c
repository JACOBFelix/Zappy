#include <stdlib.h>
#include "network.h"

static t_mail_action g_mail_action_list[PLAYER_ACTION_NB] =
{
  {&mail_handle_forward, 7, NULL},
  {&mail_handle_right, 7, NULL},
  {&mail_handle_left, 7, NULL},
  {&mail_handle_watch, 7, NULL},
  {&mail_handle_inventary, 1, NULL},
  {&mail_handle_take, 7, NULL},
  {&mail_handle_drop, 7, NULL},
  {&mail_handle_eject, 7, NULL},
  {&mail_handle_broadcast, 7, NULL},
  {&mail_handle_incantation, 300, NULL},
  {&mail_handle_fork, 42, NULL},
  {&mail_handle_connect_nbr, 0, NULL},
};

int	mail_handle(t_server *infos, t_mail *msg)
{
  msg->from->action.clock = clock() * 1000 / CLOCKS_PER_SEC
    + g_mail_action_list[msg->action].clock
    * 1000 / infos->exec_delay;
  msg->from->action.handler = g_mail_action_list[msg->action].handler;
  if (msg->action == INCANTATION)
    create_incantation(infos, msg);
  if (msg->action == FORK)
    graphic_cmd_send(infos, graphic_cmd_action_pfk(infos, msg->from));
  msg->from->action.mail = msg;
  return (SUCCESS);
}
