/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:45:10 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/11 19:47:48 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	mlx_destroy_window(obj->mlx_ptr, obj->win_ptr);
}
