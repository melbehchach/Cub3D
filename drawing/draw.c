#include "../cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int render_rect(t_img *img, t_rect *rect)
{
	int	i;
	int j;

	i = rect->y;
	while (i < (rect->y + rect->height))
	{
		j = rect->x;
		while (j < (rect->x + rect->width))
			my_mlx_pixel_put(img, j++, i, rect->color);
		++i;
	}
	return (0);
}

void	draw_map(t_img *img, t_parse *arr)
{
	t_rect	rect;
	int	i;
	int	j;

	i = 6;
	rect.height = TILE_SIZE;
	rect.width = TILE_SIZE;
	while (arr->content[i])
	{
		j = 0;
		while (arr->content[i][j])
		{
			rect.y = i * TILE_SIZE;
			rect.x = j * TILE_SIZE;
			if (arr->content[i][j] == '1')
			{
				rect.color = 16777215;
				rect.height = TILE_SIZE;
				rect.width = TILE_SIZE;
			}
			else if (arr->content[i][j] == '0')
			{
				rect.color = 1323670;
				rect.height = TILE_SIZE;
				rect.width = TILE_SIZE;
			}
			render_rect(img, &rect);
			if (arr->content[i][j] == 'N')
			{
				rect.color = RED;
				rect.height = TILE_SIZE / 4;
				rect.width = TILE_SIZE / 4;
				render_rect(img, &rect);
			}
			j++;
		}
		i++;
	}
}

int	escape_button_exit(int keysym, t_data *data)
{
	if (keysym == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
}

int	red_button_exit(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

// int	key_presse()
// {

// }

void	draw(t_parse *arr)
{
	t_img	img;
	t_data	obj;

	obj.mlx_ptr = mlx_init();
	obj.win_ptr = mlx_new_window(obj.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB_3D");
	img.mlx_img = mlx_new_image(obj.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.mlx_img, &img.bpp, &img.line_len, &img.endian);
	mlx_hook(obj.win_ptr, 2, 0, &escape_button_exit, &obj);
	mlx_hook(obj.win_ptr, 17, 0, &red_button_exit, &obj);
	draw_map(&img, arr);
	mlx_put_image_to_window(obj.mlx_ptr, obj.win_ptr, img.mlx_img, 0, 0);
	mlx_loop(obj.mlx_ptr);
	mlx_destroy_window(obj.mlx_ptr, obj.win_ptr);
	free(obj.mlx_ptr);
}