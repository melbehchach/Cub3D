#include "cub.h"

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

static void number_of_lines(char *file, t_parse *obj)
{
	obj->num_line = 0;
	obj->fd = open_file(file);
	if (obj->fd < 0)
		return ;
	while (get_next_line(obj->fd))
		obj->num_line++;
	close(obj->fd);
	// return (obj->num_line);
}

static void	allocation_for_check(char *file, int size, t_parse *obj)
{
	obj->iter = 0;
	obj->content = malloc((sizeof(char *) * size) + 1);
	if (!obj->content)
	{
		obj->content = NULL;
		return;
	}
	obj->fd = open_file(file);
	while (size > 0)
	{
		obj->line = get_next_line(obj->fd);
		obj->length = ft_strlen(obj->line);
		obj->content[obj->iter] = malloc((sizeof(char) * obj->length) + 1);
		if (!obj->content[obj->iter])
		{
			obj->content[obj->iter] = NULL;
			return;
		}
		ft_strlcpy(obj->content[obj->iter], obj->line, obj->length);
		size--;
		obj->iter++;
	}
}

// static void	filter_content(t_parse *obj)
// {

// }

int	parse(char *file)
{
	t_parse *obj;

	obj = malloc(sizeof(t_parse) * 1);
	if (!obj)
	{
		obj = NULL;
		return (0);
	}
	number_of_lines(file, obj);
	printf("%d\n", obj->num_line);
	return(0);
	allocation_for_check(file, obj->num_line, obj);
	obj->iter = 0;
	while (obj->iter < 23)
	{
		printf("%s\n", obj->content[obj->iter]);
		obj->iter++;
	}
	return (0);
}

// puts("[DEBUG]");