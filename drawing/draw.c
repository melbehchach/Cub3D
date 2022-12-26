#include "../cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
			mlx_pixel_put(img->mlx_ptr, img->win_ptr, j++, i, color);
		++i;
	}
}

void	draw(void)
{
	t_img	img;
	t_data	obj;
	// int i;
	// int j;

	obj.mlx_ptr = mlx_init();
	obj.win_ptr = mlx_new_window(obj.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB_3D");
	img.mlx_img = mlx_new_image(obj.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	// i = 0;
	// while (i < (WIN_WIDTH))
	// {
	// 	j = 0;
	// 	while (j < (WIN_HEIGHT / 2))
	// 	{
	// 		my_mlx_pixel_put(&img, i, j, 9180260);
	// 		j++;
	// 	}
	// 	i++;
	// }
	mlx_put_image_to_window(obj.mlx_ptr, obj.win_ptr, img.mlx_img, 0, 0);
	mlx_loop(obj.mlx_ptr);
	mlx_destroy_window(obj.mlx_ptr, obj.win_ptr);
	free(obj.mlx_ptr);
}