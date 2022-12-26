#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include "./minilibx/mlx.h"
#include "./get_next_line/get_next_line.h"

#define WIN_WIDTH 900
#define WIN_HEIGHT 600
#define RED 0xFF0000
#define TILE_SIZE 32

typedef struct s_parse
{
	char	**content;
	char	*line;
	int		size;
	int		nb_line;
	int		length;
	int		length2;
	int		length3;
	int		index;
	int		player;
	int		fd;
}t_parse;

typedef struct s_wall
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}t_wall;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;



/****************************************************/
/*				UTIL FUNCTIONS						*/
/****************************************************/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*create_array(int size);
char	**create_2d_array(int size);
t_parse	*create_struct(void);
void	ft_puterrmsg(char *msg);
int		open_file(char *file);



/****************************************************/
/*				PARSING FUNCTIONS					*/
/****************************************************/

int		file_name_checker(char *file);
int		create_content_array(t_parse *obj, char *file);
int 	check_direction_elements(t_parse *obj);
int		borders_checker(int nb_line, t_parse *obj);
int		check_player(t_parse *obj);
int		check_map(t_parse *obj);
int		parse(char *file);



/****************************************************/
/*				DRAW FUNCTIONS						*/
/****************************************************/

// void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw(void);


#endif