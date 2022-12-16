#include "cub.h"

void ft_puterrmsg(char *msg)
{
	int i;

	i = 0;
	while (msg[i])
	{
		write(2, &msg[i], 1);
		i++;
	}
}
