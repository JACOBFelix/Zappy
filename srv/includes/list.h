#ifndef LIST_H_
# define LIST_H_

# include <stdint.h>
# include "typedefs.h"

struct			s_list
{
  void			*data;
  struct s_list		*next;
};

int		list_push_front(t_list **list, void *data);
void		list_pop_front(t_list **list);
void		list_pop_back(t_list **list);
void		list_free_list(t_list **list);
uint32_t	list_size(t_list *list);
t_list		*list_search_elem(t_list *list,
				  void *data,
				  int (*fct_compar)(void *, void *));
t_list		*list_del_elem(t_list **list, t_list *elem);
int		list_push_back(t_list **list, void *data);
t_list		*list_get_back(t_list *list);
void		remove_node(t_list **list, t_list *elem);

#endif /* !LIST_H_ */
