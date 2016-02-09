#include <stdlib.h>
#include "server.h"

static t_list	*get_prev_node(t_list **from, t_list *list)
{
  t_list	*tmp;

  tmp = *from;
  while (tmp->next != list)
    tmp = tmp->next;
  return (tmp);
}

void		swap_node_from_list(t_list **from,
				    t_list **to,
				    t_list *elem)
{
  t_list	*prev_node;

  if (*from == elem)
    *from = elem->next;
  else
    {
      prev_node = get_prev_node(from, elem);
      prev_node->next = elem->next;
    }
  prev_node = get_prev_node(to, NULL);
  prev_node->next = elem;
  elem->next = NULL;
}

void		remove_node(t_list **list UNUSED, t_list *elem UNUSED)
{
  t_list	*tmp;

  if (elem == NULL)
    return ;
  if (*list == elem)
    {
      *list = (*list)->next;
      free(elem);
      return ;
    }
  tmp = *list;
  while (tmp)
    {
      if (tmp->next == elem)
	{
	  if (elem != NULL)
	    tmp->next = elem->next;
	  free(elem);
	  return ;
	}
      tmp = tmp->next;
    }
}
