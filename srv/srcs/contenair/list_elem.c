#include <stdlib.h>
#include "server.h"

t_list	*list_get_back(t_list *list)
{
  while (list != NULL)
    {
      if (list->next == NULL)
	return (list);
      list = list->next;
    }
  return (list);
}

uint32_t	list_size(t_list *list)
{
  uint32_t	i;

  i = 0;
  while (list != NULL)
    {
      ++i;
      list = list->next;
    }
  return (i);
}

t_list		*list_search_elem(t_list *list,
				  void *data,
				  int (*fct_compar)(void *, void *))
{
  while (list)
    {
      if (fct_compar(data, list->data) == SUCCESS)
	return (list);
      list = list->next;
    }
  return (NULL);
}

t_list		*list_del_elem(t_list **list, t_list *elem)
{
  t_list	*tmp;
  t_list	*prev;

  tmp = *list;
  prev = (t_list *)0;
  if (tmp && elem)
  {
    while (tmp && tmp != elem)
    {
      prev = tmp;
      tmp = tmp->next;
    }
    if (tmp)
    {
      if (prev)
	prev->next = tmp->next;
      else
	*list = tmp->next;
      free(elem->data);
      free(elem);
    }
  }
  return (*list);
}
