#ifndef DISPLAY_H_
# define DISPLAY_H_

# include "SDL/SDL.h"
# include "SDL/SDL_image.h"
# include "SDL/SDL_ttf.h"
# include "server.h"

typedef struct	s_coordinates
{
  int		x;
  int		y;
}		t_coordinates;

typedef struct	s_camera_move
{
  int		x;
  int		y;
}		t_camera_move;

typedef struct	s_display
{
  int		quit;
  int		loop;
  int		camera_x;
  int		camera_y;
  SDL_Event	e;
  SDL_Surface	*w;
  SDL_Surface	*loading_screen;
  SDL_Surface	*ls_end;
  SDL_Surface	*inventory;
  SDL_Surface	*playerinfo;
  SDL_Surface	*tile;
  SDL_Surface	*egg;
  SDL_Surface	*fx_evo;
  SDL_Surface	*fx_egg;
  SDL_Surface	*ponies[8];
  SDL_Surface	*rocks[7];
  TTF_Font	*font;
  SDL_Color	black;
  t_camera_move beholder;
}		t_display;

int	display_loading_screen(t_display *, int);
void	load_images(t_display *);
void	keyboard_events(t_display *d, t_server *s);

#ifndef PLAYER_ACTIONS_H_
# define PLAYER_ACTIONS_H_

# include "positions.h"

typedef enum	e_incantation_join
  {
    JOINABLE,
    UNJOINABLE
  }		t_incantation_join;

typedef struct		s_incantation
{
  t_pos			pos;
  int			success;
  t_player		**player;
}			t_incantation;

#endif /* !PLAYER_ACTIONS_H_ */

int	manage_display(t_display *d, t_server *s);
int	init_display(t_display *d);
void	close_display(t_display *d, int abort);

int	display_image(int x, int y, SDL_Surface *src, SDL_Surface *dest);
int	display_pony(int x, int y, SDL_Surface *src, SDL_Surface *dest);

int	display_map(t_display *d, t_server *s);

#endif /* DISPLAY_H_ */
