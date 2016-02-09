CC=		gcc

override CFLAGS+=	-Wall -W -Wextra -I ./includes -lm -g3

LDFLAGS	=	-lSDL -lSDL_image -lSDL_ttf

RM=		rm -f

NAME=		zappy_server

DIRSERVER=	./srcs

DIRSERVERARGV=		$(DIRSERVER)/argv

DIRSERVERCONTENAIR=	$(DIRSERVER)/contenair

DIRSERVERGENERATOR=	$(DIRSERVER)/generator

DIRSERVERDISPLAY=	$(DIRSERVER)/display

DIRSERVERCMD=		$(DIRSERVER)/cmd

DIRSERVERNETWORK=	$(DIRSERVER)/network

DIRSERVERMAIL	=	$(DIRSERVERNETWORK)/mail

DIRSERVERMAILTEST=	$(DIRSERVERMAIL)/test

DIRSERVERMAILHANDLE=	$(DIRSERVERMAIL)/handle

DIRSERVERGRAPHICCMD=	$(DIRSERVERNETWORK)/graphic_cmd

SERVEURSRCS=	$(DIRSERVERARGV)/main.c				\
		$(DIRSERVERARGV)/parse_commands.c		\
		$(DIRSERVERARGV)/free_teams_names.c		\
		$(DIRSERVERARGV)/get_width.c			\
		$(DIRSERVERARGV)/get_height.c			\
		$(DIRSERVERARGV)/get_teams.c			\
		$(DIRSERVERARGV)/get_delay.c			\
		$(DIRSERVERARGV)/get_clients_by_team.c		\
		$(DIRSERVERARGV)/get_port.c			\
		$(DIRSERVERARGV)/usage.c			\
		$(DIRSERVERARGV)/init_game.c			\
		$(DIRSERVERARGV)/disable_gui.c			\
		$(DIRSERVERNETWORK)/init_network.c		\
		$(DIRSERVERNETWORK)/loop_server.c		\
		$(DIRSERVERNETWORK)/add_client.c		\
		$(DIRSERVERNETWORK)/manage_client.c		\
		$(DIRSERVERNETWORK)/read_client.c		\
		$(DIRSERVERNETWORK)/write_client.c		\
		$(DIRSERVERNETWORK)/join_team.c			\
		$(DIRSERVERNETWORK)/set_position.c		\
		$(DIRSERVERNETWORK)/send_to_player.c		\
		$(DIRSERVERNETWORK)/graphic_client_init.c	\
		$(DIRSERVERNETWORK)/find_client.c		\
		$(DIRSERVERNETWORK)/food_management.c		\
		$(DIRSERVERNETWORK)/timeout_management.c	\
		$(DIRSERVERNETWORK)/manage_end.c		\
		$(DIRSERVERMAILTEST)/test1.c			\
		$(DIRSERVERMAILTEST)/test_parse.c		\
		$(DIRSERVERMAILTEST)/test_parse2.c		\
		$(DIRSERVERMAILTEST)/test_action_broadcast.c	\
		$(DIRSERVERMAIL)/recv.c				\
		$(DIRSERVERMAIL)/incantation_dead.c		\
		$(DIRSERVERMAIL)/parse.c			\
		$(DIRSERVERMAIL)/handle.c			\
		$(DIRSERVERMAIL)/handle_incantation.c		\
		$(DIRSERVERMAIL)/check_incantation.c		\
		$(DIRSERVERMAILHANDLE)/forward.c 		\
		$(DIRSERVERMAILHANDLE)/broadcast.c 		\
		$(DIRSERVERMAILHANDLE)/connect_nbr.c		\
		$(DIRSERVERMAILHANDLE)/expulse.c 		\
		$(DIRSERVERMAILHANDLE)/fork.c			\
		$(DIRSERVERMAILHANDLE)/incantation.c		\
		$(DIRSERVERMAILHANDLE)/inventary.c 		\
		$(DIRSERVERMAILHANDLE)/rotate.c			\
		$(DIRSERVERMAILHANDLE)/watch.c			\
		$(DIRSERVERMAILHANDLE)/get_item.c		\
		$(DIRSERVERDISPLAY)/debug.c			\
		$(DIRSERVERDISPLAY)/errors.c			\
		$(DIRSERVERDISPLAY)/display_images.c		\
		$(DIRSERVERDISPLAY)/display_map.c		\
		$(DIRSERVERDISPLAY)/display_setup.c		\
		$(DIRSERVERDISPLAY)/keyboard_events.c		\
		$(DIRSERVER)/is_number.c			\
		$(DIRSERVERCONTENAIR)/list_names.c		\
		$(DIRSERVERCONTENAIR)/list.c			\
		$(DIRSERVERCONTENAIR)/list_elem.c		\
		$(DIRSERVERCONTENAIR)/node.c			\
		$(DIRSERVERGENERATOR)/create_map.c		\
		$(DIRSERVERGENERATOR)/input_map.c		\
		$(DIRSERVERGRAPHICCMD)/recv.c			\
		$(DIRSERVERGRAPHICCMD)/msz.c			\
		$(DIRSERVERGRAPHICCMD)/bct.c 			\
		$(DIRSERVERGRAPHICCMD)/mct.c 			\
		$(DIRSERVERGRAPHICCMD)/tna.c			\
		$(DIRSERVERGRAPHICCMD)/pnw.c			\
		$(DIRSERVERGRAPHICCMD)/ppo.c			\
		$(DIRSERVERGRAPHICCMD)/plv.c			\
		$(DIRSERVERGRAPHICCMD)/pin.c			\
		$(DIRSERVERGRAPHICCMD)/pex.c			\
		$(DIRSERVERGRAPHICCMD)/pbc.c			\
		$(DIRSERVERGRAPHICCMD)/pic.c			\
		$(DIRSERVERGRAPHICCMD)/pie.c			\
		$(DIRSERVERGRAPHICCMD)/pfk.c			\
		$(DIRSERVERGRAPHICCMD)/pdr.c			\
		$(DIRSERVERGRAPHICCMD)/pgt.c			\
		$(DIRSERVERGRAPHICCMD)/pdi.c			\
		$(DIRSERVERGRAPHICCMD)/enw.c			\
		$(DIRSERVERGRAPHICCMD)/eht.c			\
		$(DIRSERVERGRAPHICCMD)/ebo.c			\
		$(DIRSERVERGRAPHICCMD)/edi.c			\
		$(DIRSERVERGRAPHICCMD)/sgt.c			\
		$(DIRSERVERGRAPHICCMD)/seg.c			\
		$(DIRSERVERGRAPHICCMD)/smg.c			\
		$(DIRSERVERGRAPHICCMD)/suc.c			\
		$(DIRSERVERGRAPHICCMD)/sbp.c			\
		$(DIRSERVERGRAPHICCMD)/sst.c

SERVEUROBJS=	$(SERVEURSRCS:.c=.o)

%.o:	%.c
		@printf "[\033[0;32mCompiled\033[0m] % 53s\n" $< | sed "s/ /./2g"
		@$(CC) -c -o $@ $< $(CFLAGS)

all:		$(NAME)

$(NAME):	$(SERVEUROBJS)
		@$(CC) $(SERVEUROBJS) -o $(NAME) $(CFLAGS) $(LDFLAGS)
		@printf "[\033[0;36mBuilt\033[0m] % 56s\n" $(NAME) | sed "s/ /./5g"

clean:
		@$(RM) $(SERVEUROBJS)
		@printf "[\033[0;31mDeleted\033[0m] % 54s\n" $(SERVEUROBJS) | sed "s/ /./3g"

fclean:		clean
		@$(RM) $(NAME)
		@printf "[\033[0;35mDeleted\033[0m] % 54s\n" $(NAME) | sed "s/ /./3g"

re:		fclean all

# Note: You have to add you CFLAGS="-D TEST_WHAT" to test the WHAT module
test: CFLAGS+=-D TEST_MODE
test: all

test_mail: CFLAGS+=-D TEST_MODE -D TEST_MAIL
test_mail: all

.PHONY:		clean fclean re all
