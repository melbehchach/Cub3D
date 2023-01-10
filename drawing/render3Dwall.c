/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3Dwall.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:08:14 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 13:24:47 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	render_3d(t_data *obj, t_img *img, int index, double heigth)
{
	double	i;
	double	j;

	i = obj->rect.y;
	while (i < (obj->rect.y + obj->rect.height))
	{
		j = obj->rect.x;
		while (j < (obj->rect.x + obj->rect.width))
		{
			obj->rect.color = get_texture(obj, i, index, heigth);
			my_mlx_pixel_put(img, (int)j++, i, obj->rect.color);
		}
		++i;
	}
	return (0);
}

void	render_walls(t_data *obj, int nb_ray)
{
	int	i;

	i = -1;
	obj->fov = 60 * (PI / 180);
	while (++i < nb_ray)
	{
		obj->dpplan = (WIN_WIDTH / 2) / tan(obj->fov / 2);
		obj->correctionwd = obj->ray[i].distance
			* cos(obj->ray->angle - obj->ply.rotationangle);
		obj->wallheight = ((double)TILE_SIZE / obj->correctionwd) * obj->dpplan;
		obj->tmp = obj->wallheight;
		if (obj->wallheight > WIN_HEIGHT)
			obj->wallheight = WIN_HEIGHT;
		obj->rect.x = i * WALL_STRIP_WIDTH;
		obj->rect.y = (WIN_HEIGHT / 2) - (obj->wallheight / 2);
		obj->rect.width = WALL_STRIP_WIDTH;
		obj->rect.height = obj->wallheight;
		render_ceiling(&obj->img, i, obj->rect.y);
		render_floor(&obj->img, i, (obj->rect.y + obj->wallheight));
		render_3d(obj, &obj->img, i, obj->tmp);
	}
}
