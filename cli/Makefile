NAME		= 	zappy_ai

DIR		=	srcs

SRC		=	$(DIR)/AI.cpp
SRC		+=	$(DIR)/Client.cpp
SRC		+=	$(DIR)/Player.cpp
SRC		+=	$(DIR)/Exceptions.cpp
SRC		+=	$(DIR)/Gui.cpp
SRC		+=	$(DIR)/main.cpp
SRC		+=	$(DIR)/Map.cpp
SRC		+=	$(DIR)/Network.cpp
SRC		+=	$(DIR)/Options.cpp
SRC		+=	$(DIR)/Parser.cpp
SRC		+=	$(DIR)/Tile.cpp
SRC		+=	$(DIR)/PathFinding.cpp

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	+= 	-W -Wall -Wextra
CXXFLAGS	+= 	-I includes
CXXFLAGS	+= 	-std=c++11
CXXFLAGS 	+=	-g

LDXXFLAGS	+=	-lpthread -lSDL -lSDL_image -lSDL_ttf

RM		= 	rm -f

CC		= 	g++

%.o: %.cpp
		@$(CC) -c -o $@ $<  $(CXXFLAGS)
		@printf "[\033[0;32mCompiled\033[0m] % 53s\n" $< | sed "s/ /./2g"

all:		$(NAME)

$(NAME):	$(OBJ)
		@$(CC) $(OBJ) -o $(NAME) $(LDXXFLAGS)
		@printf "[\033[0;36mBuilt\033[0m] % 56s\n" $(NAME) | sed "s/ /./5g"

clean:
		@$(RM) $(OBJ)
		@printf "[\033[0;31mDeleted\033[0m] % 54s\n" $(OBJ) | sed "s/ /./3g"

fclean:		clean
		@$(RM) $(NAME)
		@printf "[\033[0;35mDeleted\033[0m] % 54s\n" $(NAME) | sed "s/ /./3g"

re:		fclean all

.PHONY:		all clean fclean re
