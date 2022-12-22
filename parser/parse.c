#include "../cub.h"

int	parse(char *file)
{
	t_parse obj;

	if(create_content_array(&obj, file) < 0)
		return (0);
	if (check_direction_elements(&obj))
	{
		printf("Error\nProblem of directions in the map file\n");
		return (0);
	}
	if (borders_checker(6, &obj) == 0 || borders_checker((obj.size - 1), &obj) == 0)
	{
		printf("Error\nProblem in the map\n");
		return (0);
	}
	if (check_player(&obj) == 1)
	{
		printf("Error\nSomething wrong with the player\n");
		return (0);
	}
	if (check_map(&obj) == 1)
	{
		printf("Error\nProblem in the sides of the map\n");
		return (0);
	}
	// obj.index = 6;
	// while (obj.content[obj.index])
	// {
	// 	// puts(obj.content[obj.index]);
	// 	printf("line number %d it's length %zu\n", obj.index, ft_strlen(obj.content[obj.index]));
	// 	obj.index++;
	// }
	free(obj.content);
	return (0);
}