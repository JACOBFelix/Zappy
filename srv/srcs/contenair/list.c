#include <stdlib.h>
#include <string.h>
#include "server.h"

int		list_push_front(t_list **list, void *data)
{
  t_list	*new;

  if ((new = malloc(sizeof(t_list))) == NULL)
  {
    debug_msgf("list_push_front failed");
    derror("malloc");
  }
  else
  {
    new->next = *list;
    new->data = data;
    *list = new;
  }
  return ((new) ? (SUCCESS) : (FAILURE));
}

int		list_push_back(t_list **list, void *data)
{
  t_list	*new;
  t_list	*tmp;

  if ((new = malloc(sizeof(t_list))) == NULL)
  {
    debug_msgf("list_push_front failed");
    derror("malloc");
  }
  else
  {
    new->data = data;
    new->next = (t_list *)0;
    tmp = *list;
    if (tmp)
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
    else
    {
      *list = new;
    }
  }
  return ((new) ? (SUCCESS) : (FAILURE));
}

void		list_pop_front(t_list **list)
{
  t_list	*tmp;
  t_list	*next;

  if (list)
  {
    tmp = *list;
    if (tmp)
    {
      next = tmp->next;
      free(tmp->data);
      free(tmp);
      *list = next;
    }
    else
      debug_msgf("list_pop_front: empty list");
  }
}

void		list_pop_back(t_list **list)
{
  t_list	*tmp;
  t_list	*prev;

  if (list)
  {
    tmp = *list;
    prev = (t_list *)0;
    if (tmp)
    {
      while (tmp->next)
      {
	prev = tmp;
	tmp = tmp->next;
      }
      free(tmp->data);
      free(tmp);
      if (prev)
	prev->next = (t_list *)0;
      else
	*list = (t_list *)0;
    }
    else
      debug_msgf("list_pop_back: empty list");
  }
}

void		list_free_list(t_list **list)
{
  t_list	*tmp;
  t_list	*next;

  if (list)
  {
    tmp = *list;
    while (tmp)
    {
      next = tmp->next;
      free(tmp->data);
      free(tmp);
      tmp = next;
    }
    *list = (t_list *)0;
  }
}
