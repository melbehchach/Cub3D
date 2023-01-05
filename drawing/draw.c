#include "../cub.h"

static t_rect   player_initial_postion(t_parse *array)
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
			if (array->content[k][j] == 'N')
			{
                rect.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
                rect.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
            }
		}
		i++;
	}
    return(rect);
}

static void initiate_postion(t_data *obj, t_player *player)
{
    obj->rect = player_initial_postion(&obj->parser);
    player->posx = obj->rect.x;
    player->posy = obj->rect.y;
    player->turnDirection = 0;
    player->walkDirection = 0;
    player->rotationAngle = PI / 2;
    player->moveSpeed = 2.0;
    player->rotationSpeed= 2.0 * (PI / 180);
}

static int  close_red_button(t_data *obj)
{
    mlx_destroy_window(obj->mlx_ptr, obj->win_ptr);
    exit (EXIT_SUCCESS);
    return (0);
}

static int  press_hook(int key, t_data *obj)
{
    printf("%d\n", key);
    if (key == 53)
    {
        mlx_destroy_window(obj->mlx_ptr, obj->win_ptr);
        exit (EXIT_SUCCESS);
    }
    else if (key == 13)
        obj->player.walkDirection = 1;
    else if (key == 1)
        obj->player.walkDirection = -1;
    else if (key == 2)
        obj->player.walkDirection = 1;
    else if (key == 0)
        obj->player.walkDirection = -1;
    else if (key == 124)
        obj->player.turnDirection = 1;
    else if (key == 123)
        obj->player.turnDirection = -1;
    obj->key = key;
    return (0);
}

static int  release_hook(int key, t_data *obj)
{
    if (key == 13 || key == 1)
        obj->player.walkDirection = 0;
    else if (key == 2 || key == 0)
        obj->player.walkDirection = 0;
    else if (key == 123 || key == 124)
        obj->player.turnDirection = 0;
    return (0);
}

static int render(t_data *obj)
{
    double movestep;

    mlx_destroy_image(obj->mlx_ptr, obj->img.mlx_img);
    obj->img.mlx_img = mlx_new_image(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    obj->player.rotationAngle += obj->player.rotationSpeed * obj->player.turnDirection;
    movestep = obj->player.walkDirection * obj->player.moveSpeed;
    if (obj->key == 13 || obj->key == 1)
    {
        obj->player.posx += cos(obj->player.rotationAngle) * movestep;
        obj->player.posy += sin(obj->player.rotationAngle) * movestep;
        obj->rect.x = obj->player.posx;
        obj->rect.y = obj->player.posy;

    }
    else if (obj->key == 0 || obj->key == 2)
    {
        obj->player.posx += sin(obj->player.rotationAngle) * movestep;
        obj->player.posy += cos(obj->player.rotationAngle) * movestep;
        obj->rect.x = obj->player.posx;
        obj->rect.y = obj->player.posy;
    }
    render_map(&obj->img, &obj->parser);
    render_rotation_line(&obj->img, obj->rect.x, obj->rect.y, obj->player.rotationAngle);
    mlx_put_image_to_window(obj->mlx_ptr, obj->win_ptr, obj->img.mlx_img, 0, 0);
    return(0);
}

void	draw(t_data *obj)
{
    obj->mlx_ptr = mlx_init();
    obj->win_ptr = mlx_new_window(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
    obj->img.mlx_img = mlx_new_image(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    obj->img.addr = mlx_get_data_addr(obj->img.mlx_img, &obj->img.bpp, &obj->img.line_len, &obj->img.endian);
    initiate_postion(obj, &obj->player);
    mlx_hook(obj->win_ptr, 02, 1L<<0, &press_hook, obj);
    mlx_hook(obj->win_ptr, 03, 1L<<1, &release_hook, obj);
    mlx_hook(obj->win_ptr, 17, 1L<<5, &close_red_button, obj);
    render_map(&obj->img, &obj->parser);
    render_player(&obj->img, &obj->parser);
    mlx_put_image_to_window(obj->mlx_ptr, obj->win_ptr, obj->img.mlx_img, 0, 0);
    mlx_loop_hook(obj->mlx_ptr, &render, obj);
    mlx_loop(obj->mlx_ptr);
}