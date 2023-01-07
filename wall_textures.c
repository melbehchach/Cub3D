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

#include "cub3d.h"

int	get_texture(t_map *map, double y, int index, double wallheight)
{
	double		offsetx;
	double		offsety;
	int			*buffer;
	int			color;
	t_texture	tex;

	tex = choose_texture(map, index);
	if (map->ray[index].direction == 'V')
		offsetx = (map->ray[index].y / (double) TILESIZE);
	else
		offsetx = (map->ray[index].x / (double) TILESIZE);
	offsetx -= (int) offsetx;
	offsetx *= tex.width;
	offsety = (y + (wallheight / 2 - HEIGHT / 2)) * (tex.height / wallheight);
	offsety = (int) offsety;
	offsety *= tex.width;
	buffer = (int *)tex.img.addr;
	color = buffer[(int)offsety + (int)offsetx];
	return (color);
}

t_texture	choose_texture(t_map *map, int ray_id)
{
	if (map->ray[ray_id].angle >= 0
		&& map->ray[ray_id].angle <= M_PI
		&& map->ray[ray_id].direction == 'H')
		return (map->textures[0]);
	else if ((map->ray[ray_id].angle < M_PI / 2
			|| map->ray[ray_id].angle > 3 * M_PI / 2)
		&& map->ray[ray_id].direction == 'V')
		return (map->textures[1]);
	else if (map->ray[ray_id].angle > M_PI / 2
		&& map->ray[ray_id].angle < 3 * M_PI / 2
		&& map->ray[ray_id].direction == 'V')
		return (map->textures[2]);
	else
		return (map->textures[3]);
}

void	create_texture(t_map *map)
{
	int	i;

	i = -1;
	while (++i < TEXTURES)
	{
		map->textures[i].img.img = mlx_xpm_file_to_image(map->mlx_ptr,
				map->textures[i].path,
				&map->textures[i].width,
				&map->textures[i].height);
		if (!map->textures[i].img.img)
		{
			printf("Error Reading. textures\n GAME CLOSED\n");
			exit(EXIT_FAILURE);
		}
		map->textures[i].img.addr = mlx_get_data_addr(map->textures[i].img.img,
				&map->textures[i].img.bits_per_pixel,
				&map->textures[i].img.line_length,
				&map->textures[i].img.endian);
	}
}
