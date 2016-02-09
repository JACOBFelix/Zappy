#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "network.h"

static int	mail_recv_return_failure(t_player *from)
{
  send_to_player(from, CMD_KO);
  return (FAILURE);
}

int		mail_recv(t_server *infos,
			  t_player *from,
			  char *content)
{
  t_mail	*msg;
  size_t const	len = strlen(content);

  if ((msg = malloc(sizeof(t_mail))) == NULL)
    {
      derror("malloc");
      return (mail_recv_return_failure(from));
    }
  if (len > 0 && content[len - 1] == '\n')
    content[len - 1] = '\0';
  if (len == 0 || mail_serialize(msg, from, content) == FAILURE)
    {
      debug_msgf("mail_serialize: Cannot parse the message");
      free(msg);
      return (mail_recv_return_failure(from));
    }
  return (mail_handle(infos, msg));
}
