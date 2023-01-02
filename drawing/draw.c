#include "../cub.h"

static int	escape_button_exit(int keysym, t_data *data)
{
	if (keysym == 53)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
	return (0);
}

static int	red_button_exit(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
	return (0);
}

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int render_rect(t_img *img,  t_rect *rect)
{
	int	i;
	int j;
	
	i = rect->y;
	while (i < (rect->y + rect->height))
	{
		j = rect->x;
		while (j < (rect->x + rect->width))
		{
			if (i == 0 || j == (rect->x + rect->width - 1) || i == (rect->y + rect->height - 1))
				my_mlx_pixel_put(img, j++, i, 000000);
			my_mlx_pixel_put(img, j++, i, rect->color);
		}
		++i;
	}
	return (0);
}

static void	render_map(t_img *img, t_parse *array)
{
	t_rect	rect;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 5;
	while (array->content[++k])
	{
		j = -1;
		while (array->content[k][++j])
		{
			rect.x = j * TILE_SIZE;
			rect.y = i * TILE_SIZE;
			rect.height = TILE_SIZE;
			rect.width = TILE_SIZE;
			if (array->content[k][j] == '1')
				rect.color = 14474440;
			else if (array->content[k][j] == '0')
				rect.color = 3289700;
			render_rect(img, &rect);
		}
		i++;
	}
}

static void	render_player(t_img *img, t_parse *array)
{
	t_rect	rect;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 5;
	while (array->content[++k])
	{
		j = -1;
		while (array->content[k][++j])
		{
			rect.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
			rect.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
			rect.height = TILE_SIZE / 4;
			rect.width = TILE_SIZE / 4;
			if (array->content[k][j] == 'N')
			{
				rect.color = RED;
				render_rect(img, &rect);
			}
		}
		i++;
	}
}

// static int	front_move(int key, t_img *img, t_parse *array)
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
	render_map(&img, arr);
	render_player(&img, arr);
	// mlx_hook(obj.win_ptr, 2, 0, &front_move, &obj);
	mlx_put_image_to_window(obj.mlx_ptr, obj.win_ptr, img.mlx_img, 0, 0);
	mlx_loop(obj.mlx_ptr);
	mlx_destroy_window(obj.mlx_ptr, obj.win_ptr);
	free(obj.mlx_ptr);
}


