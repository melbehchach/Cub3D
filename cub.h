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

# define WIN_WIDTH 1280
# define WIN_HEIGHT 900
# define TILE_SIZE 40
# define PI 3.14159265359
# define WALL_STRIP_WIDTH 1
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
	int		nb_rows;
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

typedef struct s_dda
{
	double	dx;
	double	dy;
	double	step;
	double	xinc;
	double	yinc;
}	t_dda;

typedef struct s_pos
{
	double	x;
	double	y;
	char	direction;
	double	tmpx;
	double	tmpy;
}	t_pos;

typedef struct s_ray
{
	double	yintercept;
	double	xintercept;
	double	ystep;
	double	xstep;
	char	direction;
	int		is_up;
	int		is_down;
	int		is_right;
	int		is_left;
}	t_ray;

typedef struct s_dataray
{
	double	x;
	double	y;
	double	distance;
	double	angle;
	char	direction;
	int		type;
	double	tmpx;
	double	tmpy;
}	t_dataray;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			key;
	t_img		img;
	t_parse		parser;
	t_player	player;
	t_rect		rect;
	t_dataray	*ray;
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
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

int	cast_rays(t_data *map);
t_pos	castray(t_data *map, double rayangle, int i, int flag);
int	find_wall_hit(t_pos *pos, t_ray ray, t_data *map);
t_pos	get_vertical_intersect(t_data *map, double rayangle);
t_pos	get_horizontal_intersect(t_data *map, double rayangle);
void    render_walls(t_data *obj, int nb_ray);

#endif