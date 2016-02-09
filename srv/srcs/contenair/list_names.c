#include <string.h>
#include <stdlib.h>
#include "server.h"

static t_list_str	*create_str(char *s)
{
  t_list_str		*new;

  new = malloc(sizeof(t_list_str));
  if (new)
  {
    new->str = strdup(s);
    new->next = (t_list_str *)0;
  }
  else
  {
    print_error("could not alloc !");
  }
  return (new);
}

int32_t		push_str(t_list_str **list, char *s)
{
  t_list_str	*tmp;
  t_list_str	*new;

  tmp = *list;
  if (!(new = create_str(s)))
  {
    return (-1);
  }
  if (tmp)
  {
    while (tmp->next)
    {
      tmp = tmp->next;
    }
    tmp->next = new;
  }
  else
  {
    *list = new;
  }
  return (0);
}

void		erase_list_str(t_list_str **list)
{
  t_list_str	*tmp;
  t_list_str	*tmp_next;

  tmp = *list;
  while (tmp)
  {
    tmp_next = tmp->next;
    free(tmp->str);
    free(tmp);
    tmp = tmp_next;
  }
  *list = (t_list_str *)0;
}

uint32_t	get_size_list_str(t_list_str *list)
{
  uint32_t	nb;

  for (nb = 0; list; list = list->next)
  {
    nb += 1;
  }
  return (nb);
}
