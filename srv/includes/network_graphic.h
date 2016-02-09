#ifndef NETWORK_GRAPHIC_H_
# define NETWORK_GRAPHIC_H_

# include "server.h"
# include "network.h"

# define GRAPHIC_CMD_ACTION_NB 10

int	graphic_add_client(t_server *infos, t_player *client);
void	graphic_init_connection(t_server *infos, t_player *client);
int	graphic_cmd_handle(t_server *infos, t_mail *msg);
int	graphic_cmd_recv(t_server *infos,
			 t_player *from,
			 char *content);
void	graphic_cmd_send(t_server *infos, char *what);

char	*graphic_cmd_handle_msz(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_bct(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_mct(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_tna(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_ppo(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_plv(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_pin(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_sgt(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_sst(t_server *infos, t_mail *msg);
char	*graphic_cmd_handle_pnw(t_server *infos, t_mail *msg);

char	*graphic_cmd_action_bct(t_server *infos, int idx, int x, int y);
char	*graphic_cmd_action_ppo(t_server *infos, const t_player *player);
char	*graphic_cmd_action_plv(t_server *infos, const t_player *player);
char	*graphic_cmd_action_pin(t_server *infos, const t_player *player);
char	*graphic_cmd_action_sgt(t_server *infos);
char	*graphic_cmd_action_pnw(t_server *infos, t_player *cli);

char	*graphic_cmd_action_pex(t_server *infos, t_player *cli);
char	*graphic_cmd_action_pbc(t_server *infos, t_player *cli, char *what);
char	*graphic_cmd_action_pic(t_server *infos,
				t_mail *msg,
				t_incantation *incantation);
char	*graphic_cmd_action_pie(t_server *infos, t_player *plater, int flag);
char	*graphic_cmd_action_pfk(t_server *infos, t_player *cli);
char	*graphic_cmd_action_pdr(t_server *infos, t_player *cli, uint8_t rid);
char	*graphic_cmd_action_pgt(t_server *infos, t_player *cli, uint8_t rid);
char	*graphic_cmd_action_pdi(t_server *infos, t_player *cli);
char	*graphic_cmd_action_enw(t_server *infos, t_player *player, t_egg *eg);
char	*graphic_cmd_action_eht(t_server *infos, t_egg *egg);
char	*graphic_cmd_action_ebo(t_server *infos, t_egg *egg);
char	*graphic_cmd_action_edi(t_server *infos, t_egg *egg);
char	*graphic_cmd_action_seg(t_server *infos, char *winner_team_name);
char	*graphic_cmd_action_smg(t_server *infos, char *what);
char	*graphic_cmd_action_suc(t_server *infos, t_mail *msg);
char	*graphic_cmd_action_sbp(t_server *infos, t_mail *msg);

#endif /* !NETWORK_GRAPHIC_H_ */
