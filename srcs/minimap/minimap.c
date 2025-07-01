#include "cub3d.h"

void	place_minimap(t_game *game)
{
	mlx_image_t	*minimap;

	minimap = mlx_new_image(game->mlx, MAX_W / 10, MAX_H / 10);
	mlx_image_to_window(game->mlx, minimap, 0, 0);
	mlx_put_pixel(minimap, 0, 0, 0xFF0000FF);
}
