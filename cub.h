#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include "./minilibx/mlx.h"
#include "./get_next_line/get_next_line.h"

#define WIN_WIDTH
#define WIN_HEIGHT


typedef struct s_parse
{
	char	*line;
	int		num_line;
	int		fd;
}t_parse;

// typedef struct s_data
// {
// 	void *mlx_ptr;
// 	void *mlx_win;

// }t_data;


/****************************************************/
/*				UTIL FUNCTIONS						*/
/****************************************************/

void ft_puterrmsg(char *msg);
int	parse(char *file);





#endif