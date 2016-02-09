#include <stdlib.h>
#include <string.h>
#include "network_graphic.h"

static t_mail_action g_graphic_cmd_action_list[GRAPHIC_CMD_ACTION_NB] =
{
  {&graphic_cmd_handle_msz, 0, (NULL)},
  {&graphic_cmd_handle_bct, 0, (NULL)},
  {&graphic_cmd_handle_mct, 0, (NULL)},
  {&graphic_cmd_handle_tna, 0, (NULL)},
  {&graphic_cmd_handle_ppo, 0, (NULL)},
  {&graphic_cmd_handle_plv, 0, (NULL)},
  {&graphic_cmd_handle_pin, 0, (NULL)},
  {&graphic_cmd_handle_sgt, 0, (NULL)},
  {&graphic_cmd_handle_sst, 0, (NULL)},
  {&graphic_cmd_handle_pnw, 0, (NULL)},
};

int	graphic_cmd_handle(t_server *infos UNUSED, t_mail *msg UNUSED)
{
  msg->from->action.clock = 1;
  msg->from->action.handler = g_graphic_cmd_action_list[msg->action].handler;
  msg->from->action.mail = msg;
  return (SUCCESS);
}

int		graphic_cmd_recv(t_server *infos,
				 t_player *from,
				 char *content)
{
  t_mail	*msg;
  size_t const	len = strlen(content);

  if ((msg = malloc(sizeof(t_mail))) == (NULL))
    {
      derror("malloc");
      return (FAILURE);
    }
  if (len > 0 && content[len - 1] == '\n')
    content[len - 1] = '\0';
  if (len == 0 || mail_serialize(msg, from, content) == FAILURE)
    {
      debug_msgf("mail_serialize: Cannot parse the message");
      free(msg);
      return (FAILURE);
    }
  return (graphic_cmd_handle(infos, msg));
}

void	graphic_cmd_send(t_server *infos, char *what)
{
  if (infos->display_client != NULL)
    send_to_player(infos->display_client, what);
  free(what);
}
