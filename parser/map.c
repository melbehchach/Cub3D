/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:58:05 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 13:01:38 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	lines_counter(t_parse *obj, char *file)
{
	obj->fd = open_file(file);
	if (obj->fd < 0)
		return (-1);
	obj->nb_line = 0;
	obj->size = 0;
	while (1)
	{
		obj->line = get_next_line(obj->fd);
		if (!obj->line)
			break ;
		obj->length = ft_strlen(obj->line);
		if (obj->length > 1)
			obj->size++;
		if (obj->size > 6 && obj->length <= 1)
		{
			close(obj->fd);
			return (-1);
		}
	obj->nb_line++;
	}
	close(obj->fd);
	return (0);
}

static void	fill_map_array(t_parse *obj)
{
	obj->index = 0;
	while (obj->nb_line > 0)
	{
		obj->line = get_next_line(obj->fd);
		obj->length = ft_strlen(obj->line);
		if (obj->length > 1)
		{
			obj->content[obj->index]
				= (char *)malloc((sizeof(char) * obj->length) + 1);
			if (!obj->content[obj->index])
				return ;
			ft_strlcpy(obj->content[obj->index], obj->line, obj->length);
			obj->index++;
		}
		obj->nb_line--;
	}
}

int	create_content_array(t_parse *obj, char *file)
{
	if (lines_counter(obj, file) < 0)
		return (2);
	obj->fd = open_file(file);
	if (obj->fd < 0)
		return (2);
	if (obj->size <= 0)
	{
		printf("Error\nOops empty file !\n");
		return (2);
	}
	obj->content = (char **)malloc((sizeof(char *) * obj->size));
	if (!obj->content)
		return (2);
	fill_map_array(obj);
	close(obj->fd);
	return (0);
}
