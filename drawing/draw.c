#include "../cub.h"

static int	drawing(t_data *obj)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1000)
	{
		j = 100;
		while (j < 100 + WIN_WIDTH)
			mlx_pixel_put(obj->mlx_ptr, obj->win_ptr, j++, i, 328240);
		++i;
	}
	return (0);
}

void	draw(void)
{
	// void	*mlx_ptr;
	// void	*win_ptr;
	t_data obj;

	obj.mlx_ptr = mlx_init();
	obj.win_ptr = mlx_new_window(obj.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "test_window");
	mlx_loop_hook(obj.mlx_ptr, &drawing, &obj);
	mlx_loop(obj.mlx_ptr);
	mlx_destroy_window(obj.mlx_ptr, obj.win_ptr);
	free(obj.mlx_ptr);
}