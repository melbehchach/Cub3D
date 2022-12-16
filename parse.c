#include "cub.h"

static void	error(char *file)
{
	ft_puterrmsg(file);
	ft_puterrmsg(": ");
	perror("");
}

int	parse(char *file)
{
	t_parse *obj;

	obj = malloc(sizeof(t_parse) * 1);
	if (!obj)
	{
		obj = NULL;
		return (0);
	}
	obj->num_line = 0;
	obj->fd = open(file, O_RDWR);
	if (obj->fd < 0)
	{
		error(file);
		return (1);
	}
	obj->line = get_next_line(obj->fd);
	// while (obj->line)
	// {
		printf("%s", obj->line);
	// 	obj->num_line++;
	// }
	printf("number of line line is %d\n", obj->num_line);
	return (0);
}


// puts("[DEBUG]");