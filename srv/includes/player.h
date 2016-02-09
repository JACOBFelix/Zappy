#ifndef PLAYER_H_
# define PLAYER_H_

# include <stdint.h>
# include <time.h>
# include "positions.h"
# include "typedefs.h"

# define FOOD_HEAL_AMOUNT	126
# define DEFAULT_FOOD_AMOUNT	10
# define TIMEOUT_SEC		600

# define PPOX(player)		(player->pos.x)
# define PPOY(player)		(player->pos.y)
# define PLAYERS_POS_EQ(a, b)	(PPOX(a) == PPOX(b) && PPOY(a) == PPOY(b))

typedef enum	e_client_state
  {
    CLIENT_WAIT_TEAM = 0,
    PLAYER_WAIT_NUM,
    PLAYER_WAIT_DIM,
    PLAYER_IS_READY = 100,
    GRAPHIC_IS_READY,
  }		t_display_state;

typedef struct	s_network_buf
{
  char		*buffer;
  uint32_t	size;
  void		*ptr;
}		t_network_buf;

typedef struct s_mail	t_mail;
typedef char *(t_mail_handle_fct_ptr)(t_server *, t_mail *);

typedef struct		s_mail_action
{
  t_mail_handle_fct_ptr	*handler;
  clock_t		clock;
  t_mail		*mail;
}			t_mail_action;

struct			s_player
{
  int			state;
  uint8_t		level;
  char			*team_name;
  int			item[7];
  t_dir			dir;
  t_pos			pos;
  int			fd;
  t_list		*list_buffer_in;
  t_list		*list_buffer_out;
  t_mail_action		action;
  clock_t		clock_last_action;
  t_incantation		*incantation;
};

uint32_t	send_to_player(t_player *player, char *msg);
int		accept_client_sequence(t_server *infos,
				       t_player *client,
				       uint8_t read);
int		accept_player_sequence(t_server *infos,
				       t_player *client,
				       uint8_t read);
int		accept_graphic_sequence(t_server *infos,
					t_player *client,
					uint8_t read);

#endif /* !PLAYER_H_ */
