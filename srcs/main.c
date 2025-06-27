#include "cub3d.h"

// bool	fits_monitor(mlx_t *mlx)
// {
// 	int32_t	width;
// 	int32_t	height;

// 	mlx_get_monitor_size(0, &width, &height);
// 	if (width < MAX_W || height < MAX_H)
// 	{
// 		ft_printf("error\n");
// 		return (false);
// 	}
// 	return (true);
// }

/* initial values for direction and plane vectors.
Rotating based on direction faced */

void	init_game(t_game *game)
{
	game->dir.x = 1;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.x = 0.66;
	// if (game->map->player == 'S')
	// 	rotate(game, M_PI / 2);
	// else if (game->map->player == 'N')
	// 	rotate(game, M_PI / 1.5);
	// else if (game->map->player == 'W')
	// 	rotate(game, M_PI);
}

int main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_images	images;
	t_textures	textures;
	t_arena		arena;

	(void)argc;//
	create_arena(&arena, CAPACITY)
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&textures, 0, sizeof(t_textures));
	game.map = &map; // create a set game info function for next 5 lines
	game.images = &images;
	game.textures = &textures;
	init_cast(&game);//needs to happen after map parsing, player SNWE set
	game.mlx = initialise_mlx(game.mlx, game.map);
	initialise_images(&game, &images);
	//mlx_key_hook(game.mlx, &key_input, &game);
	mlx_loop_hook(game.mlx, &rayhook, &game);
	//mlx_loop_hook(game.mlx, &keyhook, &game);
	//mlx_loop(game.mlx);
	delete_textures(&game);
	mlx_terminate(game.mlx);
	clean_arena(&arena);
	return (0);
}
