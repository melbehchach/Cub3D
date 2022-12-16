CC = gcc
CFLAGS = -Wall -Werror -Wextra 
NAME_M = cub
HEADER = ./cub.h
SRC = ./main.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c \
		./parse.c \
		./util_functions.c

OBJ = $(SRC:.c=.o)

all: $(NAME_M)

$(NAME_M): $(OBJ)
	@$(CC) $(OBJ) ./minilibx/libmlx.a -framework OpenGL -framework AppKit -o $(NAME_M)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(HEADER)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME_M)

re : fclean all
