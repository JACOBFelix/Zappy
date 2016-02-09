#ifndef COMMANDS_H_
# define COMMANDS_H_

# include "display.h"

typedef struct	s_commands
{
  char		*cmd;
  int		(*fun)(t_display *d, char **tab);
}		t_commands;

int	parse_commands(t_display *d, char *str);

int	set_map_size(t_display *d, char **tab);
int	get_tile_content(t_display *d, char **tab);
int	get_team_name(t_display *d, char **tab);
int	create_new_player(t_display *d, char **tab);
int	set_player_position(t_display *d, char **tab);
int	set_player_level(t_display *d, char **tab);
int	set_player_inventory(t_display *d, char **tab);
int	player_expulsing(t_display *d, char **tab);
int	player_broadcasting(t_display *d, char **tab);
int	player_incantating(t_display *d, char **tab);
int	player_incantating_end(t_display *d, char **tab);
int	player_forking(t_display *d, char **tab);
int	player_dropping(t_display *d, char **tab);
int	player_getting(t_display *d, char **tab);
int	player_dying(t_display *d, char **tab);
int	egg_new(t_display *d, char **tab);
int	egg_hatching(t_display *d, char **tab);
int	egg_connecting(t_display *d, char **tab);
int	egg_dying(t_display *d, char **tab);
int	set_game_time(t_display *d, char **tab);
int	game_over(t_display *d, char **tab);
int	server_message(t_display *d, char **tab);
int	server_unknown_command(t_display *d, char **tab);
int	server_bad_parameter(t_display *d, char **tab);

#endif /* !COMMANDS_H_ */
