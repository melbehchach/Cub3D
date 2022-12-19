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
	while(1)
	{
		obj->line = get_next_line(obj->fd);
		if (!obj->line)
			break ;
		obj->length = ft_strlen(obj->line);
		if (obj->length > 1)
			obj->nb_line++;
	}
	close(obj->fd);
	obj->size = obj->nb_line;
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
		// return (-1);
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
		if (obj->length != 1)
		{
			obj->content[obj->index] = create_array(obj->length);
			if(!obj->content[obj->index])
				return (-1);
			ft_strlcpy(obj->content[obj->index], obj->line, obj->length);
			obj->index++;
		}
		obj->content[obj->index] = NULL;
		obj->nb_line--;
	}
	close(obj->fd);
	free(obj->content);
	return (0);
}

static int check_direction_name(t_parse *obj)
{
	obj->index = 0;
	while (obj->index < 6)
	{
		if (ft_strncmp(obj->content[obj->index], "NO ", 3) != 0)
		{
			printf("Error\nProblem in the direction name in the map file\n");
			return (1);
		}
		else if (ft_strncmp(obj->content[obj->index], "SO ", 3) != 0)
		{
			printf("Error\nProblem in the direction name in the map file\n");
			return (1);
		}
		else if (ft_strncmp(obj->content[obj->index], "WE ", 3) != 0)
		{
			printf("Error\nProblem in the direction name in the map file\n");
			return (1);
		}
		else if (ft_strncmp(obj->content[obj->index], "EA ", 3) != 0)
		{
			printf("Error\nProblem in the direction name in the map file\n");
			return (1);
		}
		else if (ft_strncmp(obj->content[obj->index], "F ", 2) != 0)
		{
			printf("Error\nProblem in the direction name in the map file\n");
			return (1);
		}
		else if (ft_strncmp(obj->content[obj->index], "c ", 2) != 0)
		{
			printf("Error\nProblem in the direction name in the map file\n");
			return (1);
		}
		obj->index++;
	}
	return (0);
}

static int	exetention_checker(char *path)
{
	char *extention;

	extention = ft_strrchr(path, 46);
	if (ft_strncmp(extention, ".xpm", 4) == 0)
		puts("very good results");
	else
		puts("not a good results");
	return (0);
}

static void	check_texture_path(t_parse *obj)
{
	obj->index = 0;
	while (obj->index < 6)
	{
		puts(obj->content[obj->index]);
		if (ft_strncmp(obj->content[obj->index], "NO ", 3) == 0)
		{
			exetention_checker(obj->content[obj->index]);	
		}
		else if (ft_strncmp(obj->content[obj->index], "SO ", 3) == 0)
		{
			exetention_checker(obj->content[obj->index]);	
		}
		else if (ft_strncmp(obj->content[obj->index], "WE ", 3) == 0)
		{
			exetention_checker(obj->content[obj->index]);	
		}
		else if (ft_strncmp(obj->content[obj->index], "EA ", 3) == 0)
		{
			exetention_checker(obj->content[obj->index]);	
		}
		obj->index++;
	}
}

int	parse(char *file)
{
	t_parse obj;

	if(creat_content_array(&obj, file) < 0)
		return (0);
	puts("[DEBUG]");
	if (check_direction_name(&obj))
		return (0);
	check_texture_path(&obj);
	obj.index = 0;
	// while(obj.content[obj.index])
	// {
	// 	printf("%s\n", obj.content[obj.index]);
	// 	obj.index++;
	// }
	// printf("%s\n", obj->content[obj->index]);
	// free(obj->content);
	// free(obj);
	return (0);
}
