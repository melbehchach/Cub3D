CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
NAME_M = cub
HEADER = ./cub.h
SRC = ./main.c \
		wall_textures.c \
		./util_functions.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c \
		./parser/parse.c \
		./parser/map.c \
		./parser/direction_elements.c \
		./parser/map_parser.c \
		./parser/map_parser2.c \
		./drawing/positions_calculus.c \
		./drawing/map_player_render.c \
		./drawing/render3Dwall.c \
		./drawing/raycasting.c \
		./drawing/draw.c

OBJ = $(SRC:.c=.o)

all: $(NAME_M)

$(NAME_M): $(OBJ)
	$(CC) $(OBJ) ./minilibx/libmlx.a -framework OpenGL -framework AppKit -o $(NAME_M)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME_M)

re : fclean all
