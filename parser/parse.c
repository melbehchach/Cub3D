#include "../cub.h"

static int	open_file(char *file)
{
	int fd;

	fd = open(file, O_RDWR);
	if (fd < 0)
	{
		ft_puterrmsg(file);
		ft_puterrmsg(": ");
		perror("");
		return (-1);
	}
	return (fd);
}

static void	lines_counter(t_parse *obj, char *file)
{
	obj->nb_line = 0;
	obj->fd = open_file(file);
	if (obj->fd < 0)
		return;
	while(get_next_line(obj->fd))
		obj->nb_line++;
	obj->size = obj->nb_line;
	close(obj->fd);
}

static void	verify_empty_lines(t_parse *obj, char *file)
{
	obj->index = 0;
	obj->fd = open_file(file);
	if (obj->fd < 0)
		return;
	while (obj->size > 0)
	{
		obj->line = get_next_line(obj->fd);
		obj->length = ft_strlen(obj->line);
		if (obj->length != 1)
			obj->index++;
		obj->size--;
	}
	obj->size = obj->index;
	close(obj->fd);
}

static void	creat_content_array(t_parse *obj, char *file)
{
	obj->index = 0;
	obj->fd = open_file(file);
	if (obj->fd < 0)
		return;
	obj->content = create_2d_array(obj->size);
	if (!obj->content)
		return;
	while(obj->nb_line > 0)
	{
		obj->line = get_next_line(obj->fd);
		obj->length = ft_strlen(obj->line);
		if (obj->length != 1)
		{
			obj->content[obj->index] = create_array(obj->length);
			if(!obj->content[obj->index])
				return;
			ft_strlcpy(obj->content[obj->index], obj->line, obj->length);
			obj->index++;
		}
		obj->content[obj->index] = NULL;
		obj->nb_line--;
	}
	close(obj->fd);
}

// static void	check_end_of_file(t_parse *obj)
// {
// 	obj->index = 0;
// 	while(obj->index < (obj->size - 1))
// 		obj->index++;
	
// 	printf("%s\n", obj->content[obj->index]);	
// }

static void check_content_array(t_parse *obj)
{
	obj->index = 0;
	puts("[DEBUG]");
	while (obj->index < 6)
	{
		if (ft_strncmp(obj->content[obj->index], "NO ", 3) > 0)
		{
			puts("Error");
			return;
		}
		else if (ft_strncmp(obj->content[obj->index], "SO ", 3) > 0)
			return;
		else if (ft_strncmp(obj->content[obj->index], "WE ", 3) > 0)
			return;
		else if (ft_strncmp(obj->content[obj->index], "EA ", 3) > 0)
			return;
		else if (ft_strncmp(obj->content[obj->index], "F ", 2) > 0)
			return;
		else if (ft_strncmp(obj->content[obj->index], "c ", 2) > 0)
			return;
		obj->index++;
	}
}

int	parse(char *file)
{
	t_parse *obj;

	obj = create_struct();
	if (!obj)
		return (0);
	lines_counter(obj, file);
	verify_empty_lines(obj, file);
	creat_content_array(obj, file);
	check_content_array(obj);
	// obj->index = 0;
	// while(obj->content[obj->index])
	// {
	// 	printf("%s\n", obj->content[obj->index]);
	// 	obj->index++;
	// }
	// printf("%s\n", obj->content[obj->index]);
	// free(obj->content);
	// free(obj);
	return (0);
}
