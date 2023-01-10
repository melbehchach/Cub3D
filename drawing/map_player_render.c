#include "../cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	render_ceiling(t_img *img, int x, double y)
{
	while (y > 0)
	{
		my_mlx_pixel_put(img, x, y, BLEU);
		y--;
	}
}

void	render_floor(t_img *img, int x, double y)
{
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(img, x, y, GREEN);
		y++;
	}
}

static int render_rect(t_img *img,  t_rect *rect)
{
	int	i;
	int j;
	
	i = rect->y;
	while (i < (rect->y + rect->height))
	{
		j = rect->x;
		while (j < (rect->x + rect->width))
			my_mlx_pixel_put(img, j++, i, rect->color);
		++i;
	}
	return (0);
}

// int render_player(t_img *img,  t_rect *rect)
// {
// 	int	i;
// 	int j;
	
// 	i = rect->y / 4;
// 	while (i < (rect->y + rect->height))
// 	{
// 		j = rect->x / 4;
// 		while (j < (rect->x + rect->width))
// 			my_mlx_pixel_put(img, j++, i, RED);
// 		++i;
// 	}
// 	return (0);
// }


void	render_map(t_img *img, t_parse *array)
{
	t_rect	rect;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 5;
	while (++k < array->size)
	{
		j = -1;
		array->length = ft_strlen(array->content[k]);
		while (++j < array->length)
		{
			rect.x = j * (TILE_SIZE * 0.2);
			rect.y = i * (TILE_SIZE * 0.2);
			rect.height = TILE_SIZE * 0.2;
			rect.width = TILE_SIZE * 0.2;
			if (array->content[k][j] == '1')
				rect.color = BLACK;
			if (array->content[k][j] == '0' || array->content[k][j] == ' ')
				rect.color = WHITE;
			render_rect(img, &rect);
		}
		++i;
	}
}