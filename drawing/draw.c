/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:07:39 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 15:57:04 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	close_red_button(t_data *obj)
{
	mlx_destroy_window(obj->mlx_ptr, obj->win_ptr);
	exit (EXIT_SUCCESS);
	return (0);
}

static int	re_render(t_data *obj)
{
	int x;
	int y;
	double newx = 0.0f, newy = 0.0f;
	char ** map = &obj->parser.content[6];
	mlx_destroy_image(obj->mlx_ptr, obj->img.mlx_img);
	obj->img.mlx_img = mlx_new_image(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	obj->img.addr = mlx_get_data_addr
		(obj->img.mlx_img, &obj->img.bpp, &obj->img.line_len, &obj->img.endian);
	obj->ply.rotationangle += obj->ply.rotationspeed * obj->ply.turndirection;
	obj->ply.movestep = obj->ply.walkdirection * obj->ply.movespeed;
	if (obj->key == 13 || obj->key == 1)
	{
		newx =  obj->ply.posx + cos(obj->ply.rotationangle) * obj->ply.movestep;
		newy =   obj->ply.posy + sin(obj->ply.rotationangle) * obj->ply.movestep;
	}
	else if (obj->key == 0)
	{	
		newx =  obj->ply.posx + cos(obj->ply.rotationangle + (M_PI_2)) * obj->ply.movestep;
		newy =   obj->ply.posy + sin(obj->ply.rotationangle + (M_PI_2)) * obj->ply.movestep;
	}
	else if (obj->key == 2)
	{
		newx =  obj->ply.posx - cos(obj->ply.rotationangle - (M_PI_2)) * obj->ply.movestep;
		newy =   obj->ply.posy - sin(obj->ply.rotationangle - (M_PI_2)) * obj->ply.movestep;
	}
	x = floor(obj->ply.posx) / TILE_SIZE;
	y = floor(newy) / TILE_SIZE;
	if (map[y][x] == '0' || map[y][x] == 'N' )//|| map[y][x] == 'S'
		// || map[y][x] == 'W' || map[y][x] == 'E')
		obj->ply.posy = newy;
	y = floor(obj->ply.posy) / TILE_SIZE;
	x = floor(newx) / TILE_SIZE;
	if (map[y ][x] == '0' || map[y][x] == 'N')// || map[y][x] == 'S'
		// || map[y][x] == 'W' || map[y][x] == 'E')
		obj->ply.posx = newx;
	obj->rect.x = obj->ply.posx;
	obj->rect.y = obj->ply.posy;
	cast_rays(obj);
	render_map(&obj->img, &obj->parser);
	render_player(&obj->img, &obj->rect);
	mlx_put_image_to_window(obj->mlx_ptr, obj->win_ptr, obj->img.mlx_img, 0, 0);
	return (0);
}

static void	hooks(t_data *obj)
{
	mlx_hook(obj->win_ptr, 02, 1L << 0, &press_hook, obj);
	mlx_hook(obj->win_ptr, 03, 1L << 1, &release_hook, obj);
	mlx_hook(obj->win_ptr, 17, 1L << 5, &close_red_button, obj);
	mlx_loop_hook(obj->mlx_ptr, &re_render, obj);
}

void	draw(t_data *obj)
{
	obj->mlx_ptr = mlx_init();
	obj->win_ptr = mlx_new_window(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	obj->img.mlx_img = mlx_new_image(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	obj->img.addr = mlx_get_data_addr
		(obj->img.mlx_img, &obj->img.bpp, &obj->img.line_len, &obj->img.endian);
	initiate_player_vars(obj, &obj->ply);
	hooks(obj);
	mlx_put_image_to_window(obj->mlx_ptr, obj->win_ptr, obj->img.mlx_img, 0, 0);
	mlx_loop(obj->mlx_ptr);
}
