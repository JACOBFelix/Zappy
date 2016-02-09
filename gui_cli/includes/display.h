#ifndef DISPLAY_H_
# define DISPLAY_H_

# include <poll.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>

enum	e_status
  {
    IDLE,
    WALKING,
    BUMPING,
    DEAD,
    DROPPING,
    TALKING,
    INCANTATING,
    FORKING,
    HATCHING
  };

typedef struct	s_bindings
{
  int		x;
  int		y;
  SDLKey	key;
}		t_bindings;

typedef struct	s_coord
{
  int		x;
  int		y;
}		t_coord;

typedef struct	s_egg
{
  t_coord	pos;
  int		id;
  enum e_status	status;
}		t_egg;

/*
** This structure contains every useful information about the player :
** its position, its status and its orientation. It also contains the id
** of the player as stocked in the server.
*/
typedef struct	s_player
{
  t_coord	pos;
  t_coord	new_pos;
  int		lv;
  int		id;
  int		resources[7];
  char		*team_name;
  enum e_status status;
  int		dir;
  int		status_time;
}		t_player;

typedef struct	s_tile
{
  t_coord	coords;
  int		resources[7];
  int		water;
}		t_tile;

typedef struct	s_map
{
  int		width;
  int		height;
  int		nb_tiles;
  t_tile	*tiles;
}		t_map;

typedef struct	s_network
{
  int		fd;
  struct pollfd	pollfds[1];
}		t_network;

/*
** Main display structure. Contains every image, the player list,
** the camera position and useful informations about the game such as the
** time or the map size.
*/
typedef struct	s_display
{
  t_map		map;
  t_player	players[1000];
  t_egg		eggs[1000];
  int		nb_players;
  int		nb_eggs;
  int		time;
  int		quit;
  int		loop;
  SDL_Event	e;
  SDL_Surface	*w;
  SDL_Surface	*loading_screen;
  SDL_Surface	*ls_end;
  SDL_Surface	*egg;
  SDL_Surface	*fx_evo;
  SDL_Surface	*fx_egg;
  SDL_Surface	*time_infos;
  SDL_Surface	*tiles[16];
  SDL_Surface	*ponies[8];
  SDL_Surface	*rocks[7];
  TTF_Font	*font;
  SDL_Color	black;
  SDL_AudioSpec	wav_spec;
  Uint32	wavlen;
  Uint8		*wavbuff;
  int		music_on;
  t_coord	camera;
  t_coord	beholder;
}		t_display;

int	parse_arguments(int ac, char **av, int *fd, t_network *network);

int	parse_command(t_display *d, char *str);

void	keyboard_events(t_display *d, Uint32 time_elapsed, int fd_server);

int	display_image(t_coord c, SDL_Surface *src, SDL_Surface *dest);
int	display_pony(t_coord c, t_display *d, t_player *p);
int	display_loading_screen(t_display *d, int loaded);

int	display_pony_bump(t_coord c, t_display *d, t_player *p);
int	display_egg_opening(t_coord c, int loop,
			    SDL_Surface *dest, SDL_Surface *img);
int	display_animation(t_coord c, SDL_Surface *src, t_display *d);

int	display_map(t_display *d);

int	display_ui(t_display *d);

char	**str_to_wordtab(char *const str, char const *const sep);

int	init_map(t_display *d);

int	launch_music(t_display *d);

int	init_display(t_display *d);
void	close_display(t_display *d);

int	get_player(t_display *d, int id);
int	get_egg(t_display *d, int id);

int	network_init(char const *const ip,
		     char const *const port,
		     t_network *const network);

void	network_close(t_network *const network);

#endif /* !DISPLAY_H_ */
