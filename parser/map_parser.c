#include "../cub.h"

static int	check_sides(char *line, int length)
{
	if (line[0] != 32 && line[0] != '1')
	{
		printf("problem at the beginnig of the line\n");
		return (1);
	}
	else if ((line[length - 1] != '1'))
	{
		printf("problem at the end of the line\n");
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
		if (line[i] == '0')
		{
			if (line[i - 1] == 32)
			{
				printf("befor the 0 fund space\n");
				return (1);
			}
			else if (line[i + 1] == 32)
			{
				printf("after the 0 found space\n");
				return (1);
			}
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
				printf("something wrrong at the top of 0\n");
				return (1);
			}
			else if (!line3[i] || line3[i] == 32)
			{
				printf("something wrrong at the bottom of 0\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	map_filter(char **array, int size)
{
	int	i;
	int	j;

	i = 6;
	while (i < size)
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] != '1' && array[i][j] != '0' && array[i][j] != 32)
			{
				if (array[i][j] != 'N' && array[i][j] != 'S' && \
					array[i][j] != 'W' && array[i][j] != 'E')
				{
					printf("strange charatcter\n");
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
	obj->index = 6;
	if (map_filter(obj->content, obj->size) == 1)
		return (6);
	while (obj->index < (obj->size - 1))
	{
		obj->length = ft_strlen(obj->content[obj->index]);
		if (check_sides(obj->content[obj->index], obj->length) == 1)
			return (6);
		if (check_sides_of_zero(obj->content[obj->index], obj->length) == 1)
			return (6);
		else if (check_top_bottom(obj->content[obj->index], \
			obj->content[obj->index - 1], obj->content[obj->index + 1]) == 1)
			return (6);
		obj->index++;
	}
	return (0);
}