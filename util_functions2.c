/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:52:10 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/11 19:52:21 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		f;
	int		signe;

	i = 0;
	f = 0;
	signe = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		f = (f * 10) + str[i] - '0';
		i++;
	}
	return (f * signe);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}
