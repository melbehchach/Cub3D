/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilahyani <ilahyani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:21:57 by ilahyani          #+#    #+#             */
/*   Updated: 2022/10/31 22:20:55 by ilahyani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_texture	choose_texture(t_data *map, int ray_id)
{
	if (map->ray[ray_id].angle >= 0
		&& map->ray[ray_id].angle <= M_PI
		&& map->ray[ray_id].direction == 'H')
		return (map->texture[0]);
	else if ((map->ray[ray_id].angle < M_PI / 2
			|| map->ray[ray_id].angle > 3 * M_PI / 2)
		&& map->ray[ray_id].direction == 'V')
		return (map->texture[1]);
	else if (map->ray[ray_id].angle > M_PI / 2
		&& map->ray[ray_id].angle < 3 * M_PI / 2
		&& map->ray[ray_id].direction == 'V')
		return (map->texture[2]);
	else
		return (map->texture[3]);
}

int	get_texture(t_data *map, double y, int index, double wallheight)
{
	double		offsetx;
	double		offsety;
	int			*buffer;
	int			color;
	t_texture	tex;

	tex = choose_texture(map, index);
	if (map->ray[index].direction == 'V')
		offsetx = (map->ray[index].y / (double) TILE_SIZE);
	else
		offsetx = (map->ray[index].x / (double) TILE_SIZE);
	offsetx -= (int) offsetx;
	offsetx *= tex.width;
	offsety = (y + (wallheight / 2 - WIN_HEIGHT / 2)) * (tex.height / wallheight);
	offsety = (int) offsety;
	offsety *= tex.width;
	buffer = (int *)tex.img.addr;
	color = buffer[(int)offsety + (int)offsetx];
	return (color);
}

void	create_texture(t_data *map)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		map->texture[i].img.mlx_img = mlx_xpm_file_to_image(map->mlx_ptr,
				map->texture[i].path,
				&map->texture[i].width,
				&map->texture[i].height);
		if (!map->texture[i].img.mlx_img)
		{
			printf("Error Reading. texture\n GAME CLOSED\n");
			exit(EXIT_FAILURE);
		}
		map->texture[i].img.addr = mlx_get_data_addr(map->texture[i].img.mlx_img,
				&map->texture[i].img.bpp,
				&map->texture[i].img.line_len,
				&map->texture[i].img.endian);
	}
}
