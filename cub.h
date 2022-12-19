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
	char	**content;
	char	*line;
	int		size;
	int		nb_line;
	int		length;
	int		index;
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

void	ft_puterrmsg(char *msg);
t_parse	*create_struct(void);
char	*create_array(int size);
char	**create_2d_array(int size);
int		parse(char *file);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
int		file_name_checker(char *file);



#endif