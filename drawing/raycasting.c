/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 14:58:22 by ilahyani          #+#    #+#             */
/*   Updated: 2023/01/05 22:16:56 by ilahyani         ###   ########.fr       */
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

	v_dist = sqrt(pow(map->player.posx - v_pos.x, 2) + pow(map->player.posy - v_pos.y, 2));
	h_dist = sqrt(pow(map->player.posx - h_pos.x, 2) + pow(map->player.posy - h_pos.y, 2));
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

static  void rows_lines(t_parse *parser)
{
    int x;
    int y;
    
    y = 6;
    x = 0;
    parser->nb_line = 0;
    while (y < (parser->size - 1))
    {
        x++;
        y++;
    }
    parser->nb_line = x;
	printf("%d\n", x);
}

void	drawline(t_data *map, double x0, double y0)
{
	t_dda	dda;
	// int		i;

	dda.dx = map->player.posx - x0;
	dda.dy = map->player.posy - y0;
	if (fabs(dda.dx) > fabs(dda.dy))
		dda.step = fabs(dda.dx);
	else
		dda.step = fabs(dda.dy);
	dda.xinc = dda.dx / dda.step;
	dda.yinc = dda.dy / dda.step;
	// i = 0;
	// while (++i <= dda.step)
	// {
	// 	my_mlx_pixel_put(&map->img, x0 * 0.2, y0 * 0.2, RED);
	// 	x0 += dda.xinc;
	// 	y0 += dda.yinc;
	// }
}

///////////////////////////////////////////////////////

int	cast_rays(t_data *map)
{
	double	rayangle;
	int		rays;
	double	fov;

	fov = 60 * (PI / 180);
	rayangle = map->player.rotationAngle - (fov / 2);
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
    // render_map(&map->img, &map->parser);
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
		map->ray[i].distance = distance(map->player.posx, map->player.posy, pos.x, pos.y)
			* cos(rayangle - map->player.rotationAngle);
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

int	check_for_wall(t_data *map, t_pos *pos)
{
    if (map->parser.content[(int)pos->tmpy / TILE_SIZE + 6][(int)pos->tmpx / TILE_SIZE] == '1')
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
            || pos->tmpx > (ft_strlen(map->parser.content[(int)(pos->tmpy / TILE_SIZE) + 6])) * TILE_SIZE
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
	ray.xintercept = floor(map->player.posx / TILE_SIZE) * TILE_SIZE;
	if (ray.is_right)
		ray.xintercept += TILE_SIZE;
	ray.yintercept = map->player.posy + (ray.xintercept - map->player.posx) * tan(rayangle);
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
	ray.yintercept = floor(map->player.posy / TILE_SIZE) * TILE_SIZE;
	if (ray.is_down)
		ray.yintercept += TILE_SIZE;
	ray.xintercept = map->player.posx + (ray.yintercept - map->player.posy) / tan(rayangle);
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