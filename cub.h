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

# define WIN_WIDTH 1700
# define WIN_HEIGHT 900
# define TILE_SIZE 36
# define PI 3.14159265359
# define RED 14423572
# define WHITE 14474440
# define BLEU 3289700
# define BLACK 0
# define ESC 53
# define W 13

typedef struct s_parse
{
	char	**content;
	char	*line;
	int		size;
	int		nb_line;
	int		length;
	int		index;
	int		player;
	int		fd;
}t_parse;

typedef struct s_rect
{
	double	x;
	double	y;
	char	direction;
	int		width;
	int		height;
	int		color;
}t_rect;

typedef	struct s_player
{
	double	posx;
	double	posy;
	double	walkDirection;
	double	turnDirection;
	double	rotationAngle;
	double	moveSpeed;
	double	moveStep;
	double	rotationSpeed;
}t_player;

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
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_parse		parser;
	t_player	player;
	t_rect		rect;
	int			key;
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
int			file_name_checker(char *file);
int			create_content_array(t_parse *obj, char *file);
int			check_direction_elements(t_parse	*obj);
int			borders_checker(int nb_line, t_parse *obj);
int			detect_player(char *line);
int			check_player(t_parse *obj);
int			check_map(t_parse *obj);
t_parse		parse(char *file);

/****************************************************/
/*				DRAW FUNCTIONS						*/
/****************************************************/
void	initiate_player_vars(t_data *obj, t_player *player);
t_rect	player_initial_postion(t_parse *array);
int		press_hook(int key, t_data *obj);
int		release_hook(int key, t_data *obj);
int		render_rotation_line(t_img *img, double x, double y, double angle);
void	render_map(t_img *img, t_parse *array);
void	draw(t_data *obj);


#endif