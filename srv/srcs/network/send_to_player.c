#include <stdlib.h>
#include <string.h>
#include "network.h"

t_network_buf	*create_buffer(char *msg)
{
  t_network_buf	*new;

  if ((new = malloc(sizeof(t_network_buf))))
  {
    if (msg == NULL)
      {
	new->buffer = NULL;
	return (new);
      }
    new->buffer = strdup(msg);
    new->size = strlen(msg);
    new->ptr = (void *)0;
  }
  else
    debug_msgf("create_buffer failed");
  if (new && !new->buffer)
  {
    free(new);
    debug_msgf("create_buffer - strdup - failed");
  }
  if (!new || !new->buffer)
    derror("malloc");
  return ((new && new->buffer) ? (new) : ((t_network_buf *)0));
}

/* The caller must free the message  */
uint32_t	send_to_player(t_player *player, char *msg)
{
  t_network_buf	*buf;

  if (player)
  {
    if ((buf = create_buffer(msg)))
    {
      list_push_back(&player->list_buffer_out, buf);
      return (SUCCESS);
    }
  }
  else
  {
    debug_msgf("send_to_player: derreferencing a null ptr");
  }
  return (FAILURE);
}
