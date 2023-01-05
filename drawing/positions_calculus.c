#include "../cub.h"

t_rect   player_initial_postion(t_parse *array)
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
			if (array->content[k][j] == 'N' || array->content[k][j] == 'S' || \
                array->content[k][j] == 'E' || array->content[k][j] == 'W')
			{
                rect.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
                rect.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
                rect.direction = array->content[k][j];
            }
		}
		i++;
	}
    return(rect);
}

void initiate_player_vars(t_data *obj, t_player *player)
{
    obj->rect = player_initial_postion(&obj->parser);
    player->posx = obj->rect.x;
    player->posy = obj->rect.y;
    player->turnDirection = 0;
    player->walkDirection = 0;
    if (obj->rect.direction == 'N')
        player->rotationAngle = 3 * PI / 2;
    else if (obj->rect.direction == 'S')
        player->rotationAngle = PI / 2;
    else if (obj->rect.direction == 'E')
        player->rotationAngle = 0;
    else if (obj->rect.direction == 'W')
        player->rotationAngle = PI;
    player->moveSpeed = 2.0;
    player->moveStep = 0;
    player->rotationSpeed= 2.0 * (PI / 180);
}

int  press_hook(int key, t_data *obj)
{
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
        obj->player.walkDirection = -1;
    else if (key == 0)
        obj->player.walkDirection = 1;
    else if (key == 124)
        obj->player.turnDirection = 1;
    else if (key == 123)
        obj->player.turnDirection = -1;
    obj->key = key;
    return (0);
}

int  release_hook(int key, t_data *obj)
{
    if (key == 13 || key == 1)
        obj->player.walkDirection = 0;
    else if (key == 2 || key == 0)
        obj->player.walkDirection = 0;
    else if (key == 123 || key == 124)
        obj->player.turnDirection = 0;
    return (0);
}