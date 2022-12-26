#include "cub.h"

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (!file_name_checker(av[1]))
	{
		printf("Error\nWrong file ! Please try again with another file.\n");
		return (0);
	}
	// parse(av[1]);
	draw();
	return (0);
}