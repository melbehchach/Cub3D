/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-behc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:58:46 by mel-behc          #+#    #+#             */
/*   Updated: 2023/01/10 13:07:13 by mel-behc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDWR);
	if (fd < 0)
	{
		printf("Error\n");
		ft_puterrmsg(file);
		ft_puterrmsg(": ");
		perror("");
		return (-1);
	}
	return (fd);
}

static void	error_msg(int code)
{
	if (code == 2)
		printf("Error\nProblem in the map lines\n");
	if (code == 3)
		printf("Error\nProblem of directions in the map file\n");
	if (code == 4)
		printf("Error\nProblem in the borders of the map\n");
	if (code == 5)
		printf("Error\nSomething wrong with the player\n");
	if (code == 6)
		printf("Error\nProblem in the map\n");
	if (code == 7)
		printf("Error\nProblem in the RGB colors\n");
	exit (EXIT_FAILURE);
}

t_parse	parse(char *file)
{
	t_parse	obj;

	if (create_content_array(&obj, file) == 2)
		error_msg(2);
	if (check_direction_elements(&obj) == 3)
		error_msg(3);
	if (borders_checker(6, &obj) == 4
		|| borders_checker((obj.size - 1), &obj) == 4)
		error_msg(4);
	if (check_player(&obj) == 5)
		error_msg(5);
	if (check_map(&obj) == 6)
		error_msg(6);
	return (obj);
}
