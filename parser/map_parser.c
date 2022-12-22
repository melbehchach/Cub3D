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
	int player;

	i = 0;
	player = 0;
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

int	check_map(t_parse *obj)
{
	int j;

	obj->index = 7;
	while (obj->index < (obj->size - 1))
	{
		obj->length = ft_strlen(obj->content[obj->index]);
		obj->length2 = ft_strlen(obj->content[obj->index - 1]);
		obj->length2 = ft_strlen(obj->content[obj->index + 1]);
		j = 0;
		puts(obj->content[obj->index]);
		printf("line number ==> %d\n", obj->index);
		while (j < obj->length)
		{
			if (obj->content[obj->index][j] == '0' && j == 0)
			{
				printf("index j ==> %d\n", j);
				puts("0 in the beginnig of the line");
				return (1);
			}
			else if ((obj->content[obj->index][j] == '0') && (j == obj->length -1))
			{
				printf("index j ==> %d\n", j);
				puts("0 in the end of the line");
				return (1);
			}
			else if ((obj->content[obj->index][j] == '0') && (j < obj->length2))
			{
				if (obj->content[obj->index - 1][j] == ' ')
				{
					printf("index j ==> %d\n", j);
					puts("space at the top of the 0");
					return (1);
				}
			}
			else if ((obj->content[obj->index][j] == '0') && (j > obj->length2))
			{
				printf("index j ==> %d\n", j);
				puts("nothing at the top of the 0");
				return (1);
			}
			else if ((obj->content[obj->index][j] == '0') && (j < obj->length3))
			{
				if (obj->content[obj->index + 1][j] == ' ')
				{
					printf("index j ==> %d\n", j);
					puts("space at the bottom of the 0");
					return (1);
				}
			}
			else if ((obj->content[obj->index][j] == '0') && (j > obj->length3))
			{
				printf("index j ==> %d\n", j);
				puts("nothing at the bottom of the 0");
				return (1);
			}
			j++;
		}
		obj->index++;
	}
	return (0);
}