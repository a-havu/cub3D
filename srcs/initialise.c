#include "../incl/cub3d.h"

mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map)
{
	mlx = mlx_init(MAX_W, MAX_H, "cub3D", true);
	if (!mlx)
		exit_process(map); //error msg "MLX initialisation failed\n"
	return (mlx);
}
