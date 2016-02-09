#ifndef NETWORK_H_
# define NETWORK_H_

# include "server.h"
# include "network_graphic.h"

# define PLAYER_ACTION_NB 12
# define CMD_OK "ok\n"
# define CMD_KO "ko\n"

typedef enum	e_action
  {
    FORWARD = 0,
    RIGHT,
    LEFT,
    WATCH,
    INVENTARY,
    TAKE,
    DROP,
    EJECT,
    BROADCAST,
    INCANTATION,
    FORK,
    CONNECT_NBR,
    GC_MSZ = 0,
    GC_BCT,
    GC_MCT,
    GC_TNA,
    GC_PPO,
    GC_PLV,
    GC_PIN,
    GC_SGT,
    GC_SST,
    GC_PNW,
  }		t_action;

typedef struct		s_mail
{
  t_player		*from;
  t_action		action;
  char			*data;
  int			type;
}			t_mail;

typedef struct	s_mail_parse
{
  char		*str;
  t_action      action;
  int	        argument;
  int		state;
}		t_mail_parse;

int	mail_recv(t_server *infos,
		  t_player *from,
		  char *content);
int	mail_serialize(t_mail *msg,
		       t_player *from,
		       char *content);
int	mail_serialize_arguments(t_mail *msg,
				 char *content);

int	mail_handle(t_server *infos, t_mail *msg);
void	check_incantation(t_player *player);
void	create_incantation(t_server *infos, t_mail *msg);
int	can_incantation(t_server *infos, t_player *player);
void	remove_item_incantation(t_server *infos,
				t_incantation *incantation,
				t_player *player);
char	*mail_handle_forward(t_server *infos, t_mail *msg);
char	*mail_handle_right(t_server *infos, t_mail *msg);
char	*mail_handle_left(t_server *infos, t_mail *msg);
char	*mail_handle_watch(t_server *infos, t_mail *msg);
char	*mail_handle_inventary(t_server *infos, t_mail *msg);
char	*mail_handle_take(t_server *infos, t_mail *msg);
char	*mail_handle_drop(t_server *infos, t_mail *msg);
char	*mail_handle_eject(t_server *infos, t_mail *msg);
char	*mail_handle_broadcast(t_server *infos, t_mail *msg);
char	*mail_handle_incantation(t_server *infos, t_mail *msg);
char	*mail_handle_fork(t_server *infos, t_mail *msg);
char	*mail_handle_connect_nbr(t_server *infos, t_mail *msg);
char	*item_on_case(t_server *infos, t_pos pos);
int     handle_get_case(char **ret, char *tmp);
void	remove_incantation(t_server *infos, t_incantation *incantation);
void	send_incantation_graphic(t_server *infos, t_player *player, int flag);
float		distance(int32_t x1, int32_t y1, int32_t x2, int32_t y2);
uint32_t	index_max_float(float const *tab, uint32_t size);
uint32_t	action_broadcast_find_angle(t_pos const *player,
					    t_pos const *target);
t_pos		action_broadcast_find_nearest_position(t_server *infos,
						       t_pos *player,
						       t_pos *target);
void		manage_end(t_server *);
int		test_mail_parsing_simple_failure1();
int		test_mail_parsing_simple_success1();
int		test_mail_parsing_simple_success2();
int		test_mail_parsing_simple_success2_1();
int		test_mail_parsing_simple_success2_2();
int		test_mail_parsing_simple_success2_3();
int		test_mail_action_broadcast();
int		test_mail_action_broadcast_distance();
int		test_mail_action_broadcast_index_max_float();
int		test_mail_action_broadcast_find_angle();

void		end_game(t_server *, t_mail *msg);
int32_t		loop_server(t_server *);
void		add_client(t_server *);
int		handle_client(t_server *infos,
			      t_player *client);
int32_t		manage_client(t_server *,
			      struct pollfd *);
int32_t		read_client(t_server *, t_player *);
void		write_client(t_player *);
void		check_dead_incantation(t_player *player);
void		*delete_client(t_server *infos, t_player *del);
int		join_team(t_server *, t_player *);
void		end_create_incantation(t_server *, t_mail *, t_incantation *);
void		init_incantation(t_server *, t_mail *, t_incantation *);
void		set_position(t_server *, t_player *);
void		disconnect_player(t_server *infos, t_player *player);
void		disconnect_graphic(t_server *infos, t_player *client);
t_player	*find_player_from_id(t_server *infos, int id);
int		find_team_from_name(t_server *infos, char *team_name);
t_egg		*find_egg_from_id(t_server *infos, uint32_t id);

uint32_t	get_food_amount_to_remove(t_server *infos);
int		player_food_management(t_server *infos,
				       t_player *player,
				       uint32_t food);
int		player_timeout_management(t_server *infos,
					  t_player *player);

#endif /* !NETWORK_H_ */
