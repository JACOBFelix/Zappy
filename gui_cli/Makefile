NAME	=	zappy_gui

SRC	=	srcs/main.c \
		srcs/music.c \
		srcs/parse_arguments.c \
		srcs/network.c \
		srcs/display_animations.c \
		srcs/display_images.c \
		srcs/display_map.c \
		srcs/display_quit.c \
		srcs/display_setup.c \
		srcs/display_ui.c \
		srcs/keyboard_events.c \
		srcs/parser.c \
		srcs/bad_inputs.c \
		srcs/create_new_player.c \
		srcs/egg.c \
		srcs/get_player.c \
		srcs/get_team_name.c \
		srcs/get_tile_content.c \
		srcs/player_status.c \
		srcs/player_status_two.c \
		srcs/server_messages.c \
		srcs/set_display_infos.c \
		srcs/set_player_infos.c

OBJ	=	$(SRC:.c=.o)

override CFLAGS	+=	-Wall -Werror -Wextra -g -I./includes
LDFLAGS	+=	-lSDL -lSDL_image -lSDL_ttf

CC	= gcc

%.o:	%.c
	@printf "[\033[0;32mCompiled\033[0m] % 53s\n" $< | sed "s/ /./2g"
	@$(CC) -c -o $@ $< $(CFLAGS)

all: 		$(NAME)

$(NAME):	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	@printf "[\033[0;36mBuilt\033[0m] % 56s\n" $(NAME) | sed "s/ /./5g"

clean:
	@$(RM) $(OBJ)
	@printf "[\033[0;31mDeleted\033[0m] % 54s\n" $(OBJ) | sed "s/ /./3g"

fclean:		clean
	@$(RM) $(NAME)
	@printf "[\033[0;35mDeleted\033[0m] % 54s\n" $(NAME) | sed "s/ /./3g"

re:		fclean all

.PHONY:	all clean fclean re
