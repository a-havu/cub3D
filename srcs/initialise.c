mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map)
{
	if (map->width * PXL > MAX_W || map->height * PXL > MAX_H)
		exit_process(map); //and print error msg "Map is too big for the screen\n"
	mlx = mlx_init(map->width * PXL, map->height * PXL, "cub3D", true);
	if (!mlx)
		exit_process(map); //error msg "MLX initialisation failed\n"
	return (mlx);
}
