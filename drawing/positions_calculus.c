/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positions_calculus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:07:56 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 13:17:39 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

t_rect	player_initial_postion(t_parse *array)
{
	t_rect	rect;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 5;
	rect.x = 0;
	rect.x = 0;
	while (++k < array->size)
	{
		j = -1;
		while (array->content[k][++j])
		{
			if (array->content[k][j] == 'N' || array->content[k][j] == 'S' || \
					array->content[k][j] == 'E' || array->content[k][j] == 'W')
			{
				rect.x = (j * TILE_SIZE) + (TILE_SIZE * 0.2);
				rect.y = (i * TILE_SIZE) + (TILE_SIZE * 0.2);
				rect.direction = array->content[k][j];
			}
		}
		i++;
	}
	return (rect);
}

void	initiate_player_vars(t_data *obj, t_player *player)
{
	obj->rect = player_initial_postion(&obj->parser);
	player->posx = obj->rect.x;
	player->posy = obj->rect.y;
	player->turndirection = 0;
	player->walkdirection = 0;
	player->sidedirection = 0;
	if (obj->rect.direction == 'N')
		player->rotationangle = 3 * PI / 2;
	else if (obj->rect.direction == 'S')
		player->rotationangle = PI / 2;
	else if (obj->rect.direction == 'E')
		player->rotationangle = 0;
	else if (obj->rect.direction == 'W')
		player->rotationangle = PI;
	player->movespeed = 3.0;
	player->movestep = 0;
	player->rotationspeed = 3.0 * (PI / 180);
}

int	press_hook(int key, t_data *obj)
{
	if (key == 53)
	{
		mlx_destroy_window(obj->mlx_ptr, obj->win_ptr);
		exit (EXIT_SUCCESS);
	}
	else if (key == 13)
		obj->ply.walkdirection = 1;
	else if (key == 1)
		obj->ply.walkdirection = -1;
	else if (key == 2)
		obj->ply.walkdirection = 1;
	else if (key == 0)
		obj->ply.walkdirection = -1;
	else if (key == 124)
		obj->ply.turndirection = 1;
	else if (key == 123)
		obj->ply.turndirection = -1;
	obj->key = key;
	return (0);
}

int	release_hook(int key, t_data *obj)
{
	if (key == 13 || key == 1)
		obj->ply.walkdirection = 0;
	else if (key == 2 || key == 0)
		obj->ply.walkdirection = 0;
	else if (key == 123 || key == 124)
		obj->ply.turndirection = 0;
	return (0);
}
