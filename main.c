#include "cub.h"

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
	draw(&obj);
	return (0);
}