#ifndef SERVER_H_
# define SERVER_H_

# include <stdint.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <poll.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <time.h>

# include "list.h"
# include "typedefs.h"
# include "positions.h"
# include "egg.h"
# include "player.h"
# include "player_actions.h"

# define UNUSED __attribute__((unused))

typedef enum	e_type
  {
    FOOD = 0,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
  }		t_type;

typedef struct		s_map
{
  int			item[7];
  int			nb_player;
  t_list		*egg_list;
  t_type		type;
  void			*addr;
  struct s_object	*next;
}			t_map;

typedef struct	s_network
{
  int		fd;
  uint8_t	alive;
  char		*local_ip;
  t_list	*client;
  struct pollfd	*fds;
}		t_network;

struct			s_server
{
  int			gui_down;
  char			**teams_names;
  uint16_t		nb_port;
  uint32_t		world_width;
  uint32_t		world_height;
  uint32_t		exec_delay;
  uint32_t		clients_by_team;
  uint32_t		nb_teams;
  t_network		network;
  t_map			*map;
  uint32_t		*nb_players_team;
  t_list		*incantation_list;
  t_list		*egg_list;
  t_player		*display_client;
  clock_t		clock;
  int			is_end;
  t_player		*winner;
};

typedef struct		s_generator_item
{
  int			proba_value;
  t_type		item_type;
}			t_generator_item;

typedef struct		s_options
{
  char			*name;
  int32_t		(*fct)(t_server *, uint32_t, uint32_t, char **);
  uint32_t		flag;
}			t_options;

typedef struct		s_list_str
{
  char			*str;
  struct s_list_str	*next;
}			t_list_str;

# define PORT_DONE	(1 << 1)
# define WIDTH_DONE	(1 << 2)
# define HEIGHT_DONE	(1 << 3)
# define TEAMS_DONE	(1 << 4)
# define NB_CLIENT_DONE	(1 << 5)
# define DELAY_DONE	(1 << 6)
# define GUI_DOWN (1 << 7)

# define PORT_DEFAULT		(4242)
# define WIDTH_DEFAULT		(50)
# define HEIGHT_DEFAULT		(50)
# define DELAY_DEFAULT		(10)
# define NB_CLIENT_DEFAULT	(10)

# define CLIENTS_MAX	(FD_SETSIZE - 1)

# define ADDR_LOCAL_IP	("8.8.8.8")
# define PORT_LOCAL_IP	(53)

# define SUCCESS		1
# define FAILURE		0

int32_t		derror(char *);
uint8_t		parse_arguments(t_server *, uint32_t, char **);
int32_t		print_error(char *);
int32_t		get_port(t_server *, uint32_t, uint32_t, char **);
int32_t		get_width(t_server *, uint32_t, uint32_t, char **);
int32_t		get_height(t_server *, uint32_t, uint32_t, char **);
int32_t		get_teams(t_server *, uint32_t, uint32_t, char **);
int32_t		get_delay(t_server *, uint32_t, uint32_t, char **);
int32_t		get_players_by_team(t_server *, uint32_t, uint32_t, char **);
int32_t   disable_gui(t_server *, uint32_t, uint32_t, char **);
void		debug_msg(char *);
void		debug_msgf(char *, ...);
int32_t		print_errorf(char *, ...);
int32_t		is_number(char *);
int32_t		push_str(t_list_str **, char *);
void		erase_list_str(t_list_str **);
uint32_t	get_size_list_str(t_list_str *);
void		free_infos(t_server *);
uint8_t		usage(char *);
int32_t		create_map(t_server *);
uint32_t	init_game(t_server *);
void		create_rand_diff_item(t_server *);
void		create_rand_special_item(t_server *, int);
void		pop_back(t_list **list);
void		pop_front(t_list **list);
int		push_front(t_list **list, void *data);
int		push_back(t_list **list, void *data);
uint32_t	list_size(t_list *list);
t_list		*list_search_elem(t_list *, void *, int (*)(void *, void *));
char		*strdup(const char *);
int		init_network(t_server *server);

#endif /* !SERVER_H_ */
