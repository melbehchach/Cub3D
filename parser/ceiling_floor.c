/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_floor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:33:45 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/11 19:33:59 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	assigne_floor_rgb(t_data *obj, char *row, int *size, char rgb)
{
	char	*color;

	color = malloc(sizeof(char) * (*size));
	if (!color)
		return (0);
	ft_strlcpy(color, row, *size + 1);
	if (rgb == 'r')
		obj->fred = ft_atoi(color);
	else if (rgb == 'g')
		obj->fgreen = ft_atoi(color);
	else if (rgb == 'b')
		obj->fbleu = ft_atoi(color);
	free(color);
	*size = 0;
	return (1);
}

void	get_floor_info(t_data *obj, char *row)
{
	int	length;
	int	comma;
	int	i;
	int	j;

	i = -1;
	j = 0;
	comma = 0;
	length = ft_strlen(row);
	while (++i < (length + 1))
	{
		if (ft_isdigit(row[i]) && row[i] != ',')
			j++;
		if (row[i] == ',' && comma == 0)
			comma += assigne_floor_rgb(obj, &row[i - j], &j, 'r');
		else if (row[i] == ',' && comma == 1)
			comma += assigne_floor_rgb(obj, &row[i - j], &j, 'g');
		else if (!row[i] && comma == 2)
			assigne_floor_rgb(obj, &row[i - j], &j, 'b');
	}
}

static int	assigne_ceiling_rgb(t_data *obj, char *row, int *size, char rgb)
{
	char	*color;

	color = malloc(sizeof(char) * (*size));
	if (!color)
		return (0);
	ft_strlcpy(color, row, *size + 1);
	if (rgb == 'r')
		obj->cred = ft_atoi(color);
	else if (rgb == 'g')
		obj->cgreen = ft_atoi(color);
	else if (rgb == 'b')
		obj->cbleu = ft_atoi(color);
	free(color);
	*size = 0;
	return (1);
}

void	get_ceiling_info(t_data *obj, char *row)
{
	int	length;
	int	comma;
	int	i;
	int	j;

	i = -1;
	j = 0;
	comma = 0;
	length = ft_strlen(row);
	while (++i < (length + 1))
	{
		if (ft_isdigit(row[i]) && row[i] != ',')
			j++;
		if (row[i] == ',' && comma == 0)
			comma += assigne_ceiling_rgb(obj, &row[i - j], &j, 'r');
		else if (row[i] == ',' && comma == 1)
			comma += assigne_ceiling_rgb(obj, &row[i - j], &j, 'g');
		else if (!row[i] && comma == 2)
			assigne_ceiling_rgb(obj, &row[i - j], &j, 'b');
	}
}
