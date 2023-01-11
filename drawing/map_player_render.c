/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:07:46 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 13:15:22 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
}

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	render_ceiling(t_data *obj, int x, double y)
{
	while (y > 0)
	{
		my_mlx_pixel_put(&obj->img, x, y, create_rgb(obj->cred, obj->cgreen, obj->cbleu));
		y--;
	}
}

void	render_floor(t_data *obj, int x, double y)
{
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&obj->img, x, y, create_rgb(obj->fred, obj->fgreen, obj->fbleu));
		y++;
	}
}

static int	render_rect(t_img *img, t_rect *rect)
{
	int	i;
	int	j;

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

void	render_map(t_img *img, t_parse *array)
{
	t_rect	rect;
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 5;
	while (++k < array->size)
	{
		j = -1;
		array->length = ft_strlen(array->content[k]);
		while (++j < array->length)
		{
			rect.x = j * (TILE_SIZE * 0.2);
			rect.y = i * (TILE_SIZE * 0.2);
			rect.height = TILE_SIZE;
			rect.width = TILE_SIZE;
			if (array->content[k][j] == '1')
				rect.color = WHITE;
			if (array->content[k][j] == '0')
				rect.color = 6579400;
			render_rect(img, &rect);
		}
		++i;
	}
}
