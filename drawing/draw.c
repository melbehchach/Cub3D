#include "../cub.h"

static int  close_red_button(t_data *obj)
{
    mlx_destroy_window(obj->mlx_ptr, obj->win_ptr);
    exit (EXIT_SUCCESS);
    return (0);
}

static int re_render(t_data *obj)
{
    mlx_destroy_image(obj->mlx_ptr, obj->img.mlx_img);
    obj->img.mlx_img = mlx_new_image(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    obj->img.addr = mlx_get_data_addr(obj->img.mlx_img, &obj->img.bpp, &obj->img.line_len, &obj->img.endian);
    obj->player.rotationAngle += obj->player.rotationSpeed * obj->player.turnDirection;
    obj->player.moveStep = obj->player.walkDirection * obj->player.moveSpeed;
    if (obj->key == 13 || obj->key == 1)
    {
        obj->player.posx += cos(obj->player.rotationAngle) * obj->player.moveStep;
        obj->player.posy += sin(obj->player.rotationAngle) * obj->player.moveStep;
    }
    else if (obj->key == 0 || obj->key == 2)
    {
        obj->player.posx += sin(obj->player.rotationAngle) * obj->player.moveStep;
        obj->player.posy += cos(obj->player.rotationAngle) * obj->player.moveStep;
    }
    obj->rect.x = obj->player.posx;
    obj->rect.y = obj->player.posy;
    cast_rays(obj);
    mlx_put_image_to_window(obj->mlx_ptr, obj->win_ptr, obj->img.mlx_img, 0, 0);
    return(0);
}

static void hooks(t_data *obj)
{
    mlx_hook(obj->win_ptr, 02, 1L<<0, &press_hook, obj);
    mlx_hook(obj->win_ptr, 03, 1L<<1, &release_hook, obj);
    mlx_hook(obj->win_ptr, 17, 1L<<5, &close_red_button, obj);
    mlx_loop_hook(obj->mlx_ptr, &re_render, obj);
}

void	draw(t_data *obj)
{
    obj->mlx_ptr = mlx_init();
    obj->win_ptr = mlx_new_window(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
    obj->img.mlx_img = mlx_new_image(obj->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
    obj->img.addr = mlx_get_data_addr(obj->img.mlx_img, &obj->img.bpp, &obj->img.line_len, &obj->img.endian);
    initiate_player_vars(obj, &obj->player);
    hooks(obj);
    cast_rays(obj);
    render_map(&obj->img, &obj->parser);
    mlx_put_image_to_window(obj->mlx_ptr, obj->win_ptr, obj->img.mlx_img, 0, 0);
    mlx_loop(obj->mlx_ptr);
}