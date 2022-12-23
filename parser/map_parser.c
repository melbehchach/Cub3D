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
			return (0);
	}
	return (1);
}

static int	detect_player(char *line)
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

int check_player(t_parse *obj)
{
	obj->index = 7;
	obj->player = 0;
	while (obj->content[obj->index])
	{
		if (detect_player(obj->content[obj->index]) == 1)
		{
			obj->player++;
			if (obj->player > 1)
				return (1);
		}
		obj->index++;
	}
	return (0);
}

static int	check_sides(char *line, int length)
{
	if (line[0] != 32 && line[0] != '1')
	{
		puts("problem at the beginnig of the line");
		return (1);
	}
	else if ((line[length - 1] != '1'))
	{
		puts("problem at the end of the line");
		return (1);
	}
	return (0);
}

static int	check_sides_of_zero(char *line, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (line[i - 1] == 32)
		{
			puts("befor the 0 fund space");
			return (1);
		}
		else if (line[i + 1] == 32)
		{
			puts("after the 0 found space");
			return (1);
		}
		i++;
	}
	return (0);
}

static int check_top_bottom(char *line, char *line2, char *line3)
{
	int	length;
	int	i;

	i = 0;
	length = ft_strlen(line);
	while (i < length)
	{
		if (line[i] == 48)
		{
			if (!line2[i] || line2[i] == 32)
			{
				puts("something wrrong at the top of 0");
				return (1);
			}
			else if (!line3[i] || line3[i] == 32)
			{
				puts("something wrrong at the bottom of 0");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	map_filter(char **array)
{
	int	i;
	int	j;

	i = 6;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] != '1' && array[i][j] != '0' && array[i][j] != 32)
			{
				if (array[i][j] != 'N' && array[i][j] != 'S' && array[i][j] != 'W' && array[i][j] != 'E')
				{
					puts("strange charatcter");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_map(t_parse *obj)
{
	obj->index = 7;
	if (map_filter(obj->content) == 1)
		return (1);
	while (obj->index < (obj->size - 1))
	{
		obj->length = ft_strlen(obj->content[obj->index]);
		if (check_sides(obj->content[obj->index], obj->length) == 1)
			return (1);
		if (check_sides_of_zero(obj->content[obj->index], obj->length) == 1)
			return (1);
		else if (check_top_bottom(obj->content[obj->index], obj->content[obj->index - 1], obj->content[obj->index + 1]) == 1)
			return (1);
		obj->index++;
	}
	return (0);
}