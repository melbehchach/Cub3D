/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:37:06 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/11 19:39:00 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static char	check_fc(char *row)
{
	char	letter;
	int		i;

	i = 0;
	letter = '\0';
	while (row[i] == 32)
		i++;
	if (row[i] == 'F')
		letter = 'F';
	else if (row[i] == 'C')
		letter = 'C';
	return (letter);
}

static int	rgb_range(int color)
{
	if (color < 0 || color > 255)
		return (0);
	return (1);
}

int	check_rgb(t_data *obj)
{
	int	i;

	i = -1;
	while (++i < 6)
	{
		if (check_fc(obj->parser.content[i]) == 'F')
			get_floor_info(obj, obj->parser.content[i]);
		else if (check_fc(obj->parser.content[i]) == 'C')
			get_ceiling_info(obj, obj->parser.content[i]);
	}
	if (!rgb_range(obj->fred))
		return (7);
	if (!rgb_range(obj->fgreen))
		return (7);
	if (!rgb_range(obj->fbleu))
		return (7);
	if (!rgb_range(obj->cred))
		return (7);
	if (!rgb_range(obj->cgreen))
		return (7);
	if (!rgb_range(obj->cbleu))
		return (7);
	return (1);
}
