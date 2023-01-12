/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:07:46 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/11 19:49:17 by mel-behc         ###   ########.fr       */
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
		my_mlx_pixel_put(&obj->img, x, y,
			create_rgb(obj->cred, obj->cgreen, obj->cbleu));
		y--;
	}
}

void	render_floor(t_data *obj, int x, double y)
{
	while (y < WIN_HEIGHT)
	{
		my_mlx_pixel_put(&obj->img, x, y,
			create_rgb(obj->fred, obj->fgreen, obj->fbleu));
		y++;
	}
}
