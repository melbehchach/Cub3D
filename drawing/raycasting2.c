/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:41:19 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 15:55:47 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_for_wall(t_data *map, t_pos *pos)
{
	if (map->parser.content[(int)pos->tmpy / TILE_SIZE
			+ 6][(int)pos->tmpx / TILE_SIZE] == '1')
		return (1);
	return (0);
}

int	find_wall_hit(t_pos *pos, t_ray ray, t_data *map)
{
	rows_lines(&map->parser);
	while (69)
	{
		set_pos(pos, ray);
		if ((pos->tmpy / TILE_SIZE) > map->parser.nb_line
			|| pos->tmpy < 0
			|| pos->tmpx > (ft_strlen(map->parser.content
					[(int)(pos->tmpy / TILE_SIZE) + 6])) * TILE_SIZE
			|| pos->tmpx < 0)
			return (0);
		if (check_for_wall(map, pos))
			return (0);
		ray.xintercept += ray.xstep;
		ray.yintercept += ray.ystep;
	}
	return (0);
}

t_pos	get_vertical_intersect(t_data *map, double rayangle)
{
	t_pos	pos;
	t_ray	ray;

	set_ray_direction(rayangle, &ray);
	ray.xintercept = floor(map->ply.posx / TILE_SIZE) * TILE_SIZE;
	if (ray.is_right)
		ray.xintercept += TILE_SIZE;
	ray.yintercept = map->ply.posy
		+ (ray.xintercept - map->ply.posx) * tan(rayangle);
	ray.xstep = TILE_SIZE;
	if (ray.is_left)
		ray.xstep *= -1;
	ray.ystep = TILE_SIZE * tanf(rayangle);
	if (ray.is_up && ray.ystep > 0)
		ray.ystep *= -1;
	else if (ray.is_down && ray.ystep < 0)
		ray.ystep *= -1;
	ray.direction = 'V';
	find_wall_hit(&pos, ray, map);
	return (pos);
}

t_pos	get_horizontal_intersect(t_data *map, double rayangle)
{
	t_pos	pos;
	t_ray	ray;

	set_ray_direction(rayangle, &ray);
	ray.yintercept = floor(map->ply.posy / TILE_SIZE) * TILE_SIZE;
	if (ray.is_down)
		ray.yintercept += TILE_SIZE;
	ray.xintercept = map->ply.posx
		+ (ray.yintercept - map->ply.posy) / tan(rayangle);
	ray.ystep = TILE_SIZE;
	if (ray.is_up)
		ray.ystep *= -1;
	ray.xstep = TILE_SIZE / tan(rayangle);
	if (ray.is_left && ray.xstep > 0)
		ray.xstep *= -1;
	else if (ray.is_right && ray.xstep < 0)
		ray.xstep *= -1;
	ray.direction = 'H';
	find_wall_hit(&pos, ray, map);
	return (pos);
}
