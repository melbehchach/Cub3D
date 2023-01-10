/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:58:38 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 13:02:32 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	borders_checker(int nb_line, t_parse *obj)
{
	int	i;

	i = 0;
	while (obj->content[nb_line][i])
	{
		if (obj->content[nb_line][i] == 32)
			i++;
		else if (obj->content[nb_line][i] == '1')
			i++;
		else
			return (4);
	}
	return (0);
}

int	detect_player(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' || line[i] == 'S')
			return (1);
		else if (line[i] == 'E' || line[i] == 'W')
			return (1);
		i++;
	}
	return (0);
}

int	check_player(t_parse *obj)
{
	obj->player = 0;
	obj->index = 6;
	while (obj->index < obj->size)
	{
		if (detect_player(obj->content[obj->index]) == 1)
		{
			obj->player++;
			if (obj->player > 1)
				return (5);
		}
		obj->index++;
	}
	return (0);
}
