/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:07:39 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/11 19:42:50 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	close_red_button(t_data *obj)
{
	mlx_destroy_window(obj->mlx_ptr, obj->win_ptr);
	free_content(obj);
	exit (EXIT_SUCCESS);
	return (0);
}

static void	move_back_front(t_data *obj)
{
	obj->newx = obj->ply.posx
		+ cos(obj->ply.rotationangle) * obj->ply.movestep;
	obj->newy = obj->ply.posy
		+ sin(obj->ply.rotationangle) * obj->ply.movestep;
}

static void	move_left_right(t_data *obj)
{
	if (obj->key == 0)
	{	
		obj->newx = obj->ply.posx
			+ cos(obj->ply.rotationangle + (M_PI_2)) * obj->ply.movestep;
		obj->newy = obj->ply.posy
			+ sin(obj->ply.rotationangle + (M_PI_2)) * obj->ply.movestep;
	}
	else if (obj->key == 2)
	{
		obj->newx = obj->ply.posx
			- cos(obj->ply.rotationangle - (M_PI_2)) * obj->ply.movestep;
		obj->newy = obj->ply.posy
			- sin(obj->ply.rotationangle - (M_PI_2)) * obj->ply.movestep;
	}
}

static void	update_position(t_data *obj)
{
	char	**map;
	int		x;
	int		y;

	map = &obj->parser.content[6];
	x = floor(obj->ply.posx) / TILE_SIZE;
	y = floor(obj->newy) / TILE_SIZE;
	if (map[y][x] == '0' || map[y][x] == 'N'
	|| map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'E')
		obj->ply.posy = obj->newy;
	y = floor(obj->ply.posy) / TILE_SIZE;
	x = floor(obj->newx) / TILE_SIZE;
	if (map[y][x] == '0' || map[y][x] == 'N'
			|| map[y][x] == 'S' || map[y][x] == 'W' || map[y][x] == 'E')
		obj->ply.posx = obj->newx;
}

int	re_render(t_data *obj)
{
	mlx_destroy_image(obj->mlx_ptr, obj->img.mlx_img);
	obj->img.mlx_img = mlx_new_image(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	obj->img.addr = mlx_get_data_addr
		(obj->img.mlx_img, &obj->img.bpp, &obj->img.line_len, &obj->img.endian);
	obj->ply.rotationangle += obj->ply.rotationspeed * obj->ply.turndirection;
	obj->ply.movestep = obj->ply.walkdirection * obj->ply.movespeed;
	if (obj->key == 13 || obj->key == 1)
		move_back_front(obj);
	else if (obj->key == 0 || obj->key == 2)
		move_left_right(obj);
	update_position(obj);
	cast_rays(obj);
	render_map(&obj->img, &obj->parser);
	mlx_put_image_to_window(obj->mlx_ptr, obj->win_ptr, obj->img.mlx_img, 0, 0);
	free(obj->ray);
	obj->ray = NULL;
	return (0);
}
