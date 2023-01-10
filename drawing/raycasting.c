/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:08:06 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 15:51:11 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	set_pos(t_pos *pos, t_ray ray)
{
	pos->x = ray.xintercept;
	pos->y = ray.yintercept;
	pos->tmpy = pos->y;
	pos->tmpx = pos->x;
	if (ray.direction == 'H' && ray.is_up)
		pos->tmpy--;
	else if (ray.direction == 'V' && ray.is_left)
		pos->tmpx--;
}

double	normalize_angle(double angle)
{
	if (angle > 2 * PI)
		return (angle - (2 * PI));
	else if (angle < 0)
		return (angle + (2 * PI));
	return (angle);
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

t_pos	get_shortest_dist(t_data *map, t_pos h_pos, t_pos v_pos)
{
	double	v_dist;
	double	h_dist;

	v_dist = sqrt(pow(map->ply.posx - v_pos.x, 2)
			+ pow(map->ply.posy - v_pos.y, 2));
	h_dist = sqrt(pow(map->ply.posx - h_pos.x, 2)
			+ pow(map->ply.posy - h_pos.y, 2));
	if (v_dist - h_dist >= 0)
		return (h_pos);
	return (v_pos);
}

void	set_ray_direction(double rayangle, t_ray *ray)
{
	if (rayangle > 0 && rayangle < PI)
		ray->is_down = 1;
	else
		ray->is_down = 0;
	if (!(ray->is_down))
		ray->is_up = 1;
	else
		ray->is_up = 0;
	if (rayangle < 0.5 * PI || rayangle > 1.5 * PI)
		ray->is_right = 1;
	else
		ray->is_right = 0;
	if (!(ray->is_right))
		ray->is_left = 1;
	else
		ray->is_left = 0;
}
