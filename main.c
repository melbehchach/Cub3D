#include "cub.h"

static char	*get_textur_path(char **array, char *str)
{
	char	*path;
	int		length;
	int		i;

	i = -1;
	while (array[++i])
	{
		if (ft_strncmp(array[i], str, 2) == 0)
			break;
	}
	length = ft_strlen(array[i]);
	path = malloc((sizeof(char) * length) + 1);
	if (!path)
		return (NULL);
	ft_strlcpy(path, array[i], length);
	return (path);
}

static void	fill_textur_array(t_data *obj)
{
	int	i;

	i = -1;
	obj->texture = (t_texture *)malloc((sizeof(t_texture) * 4));
	if (!obj->texture)
		return;
	while (++i < 4)
	{
		if (i == 0)
			obj->texture[i].path = get_textur_path(obj->parser.content, "NO");
		if (i == 1)
			obj->texture[i].path = get_textur_path(obj->parser.content, "SO");
		if (i == 2)
			obj->texture[i].path = get_textur_path(obj->parser.content, "EA");
		if (i == 3)
			obj->texture[i].path = get_textur_path(obj->parser.content, "WE");
	}
}

int main(int ac, char **av)
{
	t_data obj;

	if (ac != 2)
		return (0);
	if (!file_name_checker(av[1]))
	{
		printf("Error\nWrong file ! Please try again with another file.\n");
		return (0);
	}
	obj.parser = parse(av[1]);
	fill_textur_array(&obj);
	int i = -1;
	draw(&obj);
	return (0);
}