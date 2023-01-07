#include "../cub.h"

static int render_3D(t_img *img,  t_rect *rect)
{
	int	i;
	int j;
	

	i = rect->y;
	while (i < (rect->y + rect->height))
	{
		j = rect->x;
		while (j < (rect->x + rect->width))
        {
			my_mlx_pixel_put(img, j++, i, rect->color);
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
    double      FOV;
    int         i;

    i = -1;
    FOV = 60 * (PI / 180);
    while (++i < nb_ray)
    {
        CorrectionWallDistance = obj->ray[i].distance;
        distanceProjectionplan = (WIN_WIDTH / 2) / tan(FOV / 2);
        wallStripeHeight = (TILE_SIZE / CorrectionWallDistance) * distanceProjectionplan;
        if (wallStripeHeight > WIN_HEIGHT)
            wallStripeHeight = WIN_HEIGHT;
        obj->rect.x = i * WALL_STRIP_WIDTH;
        obj->rect.y = (WIN_HEIGHT / 2) - (wallStripeHeight / 2);
        obj->rect.width = WALL_STRIP_WIDTH;
        obj->rect.height = wallStripeHeight;
        obj->rect.color = WHITE;
        render_3D(&obj->img, &obj->rect);
    }
    
}