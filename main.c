/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 16:02:08 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 16:03:02 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*get_textur_path(char **array, char *str)
{
	char	*path;
	int		i;
	int		j;

	i = -1;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j] == 32)
			j++;
		if (ft_strncmp(&array[i][j], str, 2) == 0)
			break ;
	}
	path = ft_strchr(&array[i][j], '.');
	return (path);
}

static void	fill_textur_array(t_data *obj)
{
	int	i;

	i = -1;
	obj->texture = (t_texture *)malloc((sizeof(t_texture) * 4));
	if (!obj->texture)
		return ;
	while (++i < 6)
	{
		if (i == 0)
			obj->texture[i].path = get_textur_path(obj->parser.content, "SO");
		if (i == 1)
			obj->texture[i].path = get_textur_path(obj->parser.content, "EA");
		if (i == 2)
			obj->texture[i].path = get_textur_path(obj->parser.content, "WE");
		if (i == 3)
			obj->texture[i].path = get_textur_path(obj->parser.content, "NO");
	}
}

int	main(int ac, char **av)
{
	t_data	obj;

	if (ac != 2)
		return (0);
	if (!file_name_checker(av[1]))
	{
		printf("Error\nWrong file ! Please try again with another file.\n");
		return (0);
	}
	obj.parser = parse(av[1]);
	fill_textur_array(&obj);
	draw(&obj);
	return (0);
}
