#include "../cub.h"

static int render_3D(t_data *obj, t_img *img, int index, double heigth)
{
	double	i;
	double j;

	i = obj->rect.y;
	while (i < (obj->rect.y + obj->rect.height))
	{
		j = obj->rect.x;
		while (j < (obj->rect.x + obj->rect.width))
        {

            obj->rect.color = get_texture(obj, i, index, heigth);
			my_mlx_pixel_put(img, (int)j++, i, obj->rect.color);
        }
		++i;
	}
	return (0);
}

void    render_walls(t_data *obj, int nb_ray)
{
    double      wallStripeHeight;
    double      distanceProjectionplan;
    double      CorrectionWallDistance;
    double      tmp;
    double      FOV;
    int         i;

    i = -1;
    FOV = 60 * (PI / 180);
    while (++i < nb_ray)
    {
        distanceProjectionplan = (WIN_WIDTH / 2) / tan(FOV / 2);
        CorrectionWallDistance = obj->ray[i].distance * cos(obj->ray->angle - obj->player.rotationAngle);
        wallStripeHeight = ((double)TILE_SIZE / CorrectionWallDistance) * distanceProjectionplan;
        tmp = wallStripeHeight;
        if (wallStripeHeight > WIN_HEIGHT)
            wallStripeHeight = WIN_HEIGHT;
        obj->rect.x = i * WALL_STRIP_WIDTH;
        obj->rect.y = (WIN_HEIGHT / 2) - (wallStripeHeight / 2);
        obj->rect.width = WALL_STRIP_WIDTH;
        obj->rect.height = wallStripeHeight;
        render_3D(obj, &obj->img, i, tmp);
    }
    // puts("after render walls");
}