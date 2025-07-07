#include "cub3d.h"

mlx_t	*initialise_mlx(t_game *game)
{
	game->mlx = mlx_init(MAX_W, MAX_H, "cub3D", true);
	if (!game->mlx)
		ft_error(8, game);
	return (game->mlx);
}

//redundant?