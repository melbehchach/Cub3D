#include "../cub.h"

static int	exetention_checker(char *path)
{
	char *extention;

	extention = ft_strrchr(path, 46);
	if (ft_strncmp(extention, ".xpm", 4) == 0)
		return (1);
	return (0);
}

static int	check_direction_name(char *name)
{
	int	i;

	i = 0;
	while (name[i] == ' ')
		i++;
	if (ft_strncmp(&name[i], "NO ", 3) == 0 && exetention_checker(name))
		return (1);
	else if (ft_strncmp(&name[i], "SO ", 3) == 0 && exetention_checker(name))
		return (1);
	else if (ft_strncmp(&name[i], "WE ", 3) == 0 && exetention_checker(name))
		return (1);
	else if (ft_strncmp(&name[i], "EA ", 3) == 0 && exetention_checker(name))
		return (1);
	else if (ft_strncmp(&name[i], "F ", 2) == 0)
		return (1);
	else if (ft_strncmp(&name[i], "C ", 2) == 0)
		return (1);
	return (0);
}

static int check_duplicated(t_parse *obj)
{
	int	i;
	int	j;

	i = 0;
	while (i < 6)
	{
		j = i + 1;
		while (j < 6)
		{
			if (ft_strncmp(obj->content[i], obj->content[j], 3) == 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int check_direction_elements(t_parse *obj)
{
	int	counter;

	obj->index = 0;
	counter = 0;
	while (obj->index < 6)
	{
		if (check_direction_name(obj->content[obj->index]) == 1)
			counter++;
		obj->index++;
	}
	if (counter != 6 || check_duplicated(obj) != 1)
		return (3);
	return (0);
}