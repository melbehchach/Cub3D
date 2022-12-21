#include "../cub.h"

static int	open_file(char *file)
{
	int fd;

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

static int	lines_counter(t_parse *obj, char *file)
{
	obj->fd = open_file(file);
	if (obj->fd < 0)
		return (-1);
	obj->nb_line = 0;
	obj->size = 0;
	while(1)
	{
		obj->line = get_next_line(obj->fd);
		if (!obj->line)
			break ;
		obj->length = ft_strlen(obj->line);
		if (obj->length > 1)
			obj->size++;
		obj->nb_line++;
	}
	close(obj->fd);
	return (0);
}

static int	creat_content_array(t_parse *obj, char *file)
{
	if (lines_counter(obj, file) < 0)
		return (-1);
	obj->fd = open_file(file);
	if (obj->fd < 0)
		return (-1);
	if (obj->size <= 0)
	{
		printf("Error\nOops empty file !\n");
		exit(1);
	}
	obj->content = create_2d_array(obj->size);
	if (!obj->content)
		return (-1);
	obj->index = 0;
	while(obj->nb_line > 0)
	{
		obj->line = get_next_line(obj->fd);
		obj->length = ft_strlen(obj->line);
		if (obj->length > 1)
		{
			obj->content[obj->index] = create_array(obj->length);
			ft_strlcpy(obj->content[obj->index], obj->line, obj->length);
			obj->index++;
		}
		obj->nb_line--;
	}
	obj->content[obj->index] = NULL;
	close(obj->fd);
	return (0);
}

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
	if (ft_strncmp(name, "NO ", 3) == 0 && exetention_checker(name))
		return (1);
	else if (ft_strncmp(name, "SO ", 3) == 0 && exetention_checker(name))
		return (1);
	else if (ft_strncmp(name, "WE ", 3) == 0 && exetention_checker(name))
		return (1);
	else if (ft_strncmp(name, "EA ", 3) == 0 && exetention_checker(name))
		return (1);
	else if (ft_strncmp(name, "F ", 2) == 0)
		return (1);
	else if (ft_strncmp(name, "C ", 2) == 0)
		return (1);
	return (0);
}

static int check_direction_elements(t_parse *obj)
{
	int	counter;

	obj->index = 0;
	counter = 0;
	while (obj->index < 6)
	{
		if (check_direction_name(obj->content[obj->index]))
			counter++;
		obj->index++;
	}
	if (counter != 6)
		return (1);
	return (0);
}

static int	borders_checker(int nb_line, t_parse *obj)
{
	int	i;

	i = 0;
	while (obj->content[nb_line][i])
	{
		if (obj->content[nb_line][i] == '\t')
			i++;
		else if (obj->content[nb_line][i] == '1')
			i++;
		else
			return (0);
	}
	return (1);
}

static int map_content_checker(char *line)
{
	int i;
	int	player;

	i = 0;
	player = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			i++;
		else if (line[i] == '1')
			i++;
		else if (line[i] == '0')
			i++;
		else if (line[i] == 'N')
			i++;
		else if (line[i] == 'S')
			i++;
		else if (line[i] == 'W')
			i++;
		else if (line[i] == 'E')
			i++;
		else
			return (0);
	}
	return (1);
}

int	parse(char *file)
{
	t_parse obj;

	if(creat_content_array(&obj, file) < 0)
		return (0);
	if (check_direction_elements(&obj))
	{
		printf("Error\nProblem in the direction name in the map file\n");
		return (0);
	}
	if (borders_checker(6, &obj) == 0 || borders_checker((obj.size - 1), &obj) == 0)
	{
		printf("Error\nMap borders are not correct\n");
		return (0);
	}
	obj.index = 7;
	while(obj.index < (obj.size - 6))
	{
		if (map_content_checker(obj.content[obj.index]) == 0)
		{
			printf("line => %d\n", obj.index);
			puts("Error\nContent map is not correct");
			return (0);
		}
		obj.index++;
	}
	// free(obj.content[obj.index]);
	free(obj.content);
	return (0);
}