/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:49:49 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 16:00:53 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	rows_lines(t_parse *parser)
{
	int	x;
	int	y;

	y = 6;
	x = 0;
	parser->nb_line = 0;
	while (y < (parser->size - 1))
	{
		x++;
		y++;
	}
	parser->nb_line = x;
}

void	drawline(t_data *map, double x0, double y0)
{
	t_dda	dda;

	dda.dx = map->ply.posx - x0;
	dda.dy = map->ply.posy - y0;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.step = fabs(dda.dx);
	else
		dda.step = fabs(dda.dy);
	dda.xinc = dda.dx / dda.step;
	dda.yinc = dda.dy / dda.step;
}

int	cast_rays(t_data *map)
{
	double	rayangle;
	int		rays;
	double	fov;

	fov = 60 * (PI / 180);
	rayangle = map->ply.rotationangle - (fov / 2);
	map->ray = (t_dataray *)malloc(sizeof(t_dataray) * (WIN_WIDTH + 1));
	if (!map->ray)
		exit(1);
	rays = -1;
	while (++rays < WIN_WIDTH)
	{
		castray(map, normalize_angle(rayangle), rays, 1);
		drawline(map, map->ray[rays].x, map->ray[rays].y);
		rayangle += fov / WIN_WIDTH;
	}
	create_texture(map);
	render_walls(map, rays);
	return (0);
}

t_pos	castray(t_data *map, double rayangle, int i, int flag)
{
	t_pos	h_pos;
	t_pos	v_pos;
	t_pos	pos;

	h_pos = get_horizontal_intersect(map, rayangle);
	v_pos = get_vertical_intersect(map, rayangle);
	pos = get_shortest_dist(map, h_pos, v_pos);
	if (flag == 1)
	{
		map->ray[i].distance = distance(map->ply.posx, map->ply.posy,
				pos.x, pos.y) * cos(rayangle - map->ply.rotationangle);
		map->ray[i].x = pos.x;
		map->ray[i].y = pos.y;
		map->ray[i].angle = rayangle;
		map->ray[i].tmpx = pos.tmpx;
		map->ray[i].tmpy = pos.tmpy;
		if (pos.x == h_pos.x && pos.y == h_pos.y)
			map->ray[i].direction = 'H';
		else
			map->ray[i].direction = 'V';
	}
	return (pos);
}
