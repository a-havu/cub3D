#include "cub3d.h"
#include <stdio.h>

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

mlx_t	*initialise_mlx(mlx_t *mlx, t_arena *arena)
{
	// if (map->width * PXL > MAX_W || map->height * PXL > MAX_H)
	// 	exit_process(map, "Map is too big for screen\n", 1);
	mlx = mlx_init(MAX_W, MAX_H, "cub3D", true);
	if (!mlx)
	{
		clean_arena(arena);
		exit(EXIT_FAILURE);
	}
	return (mlx);
}

/** Rotates raycasting values according to player orientation
 * @param game	the game struct
 * @param rot	by how much we rotate player's view
 */
void rotate(t_game *game, double rot)
{
    double odx = game->dir.x;
    double ody = game->dir.y;
    double opx = game->plane.x;
    double opy = game->plane.y;

    game->dir.x   = odx * cos(rot) - ody * sin(rot);
    game->dir.y   = odx * sin(rot) + ody * cos(rot);
    game->plane.x = opx * cos(rot) - opy * sin(rot);
    game->plane.y = opx * sin(rot) + opy * cos(rot);
}

/** Sets raycasting values in game struct
 * @param game the game struct
 */
void	init_game(t_game *game)
{
	game->dir.x = 1;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
	if (game->map->player == 'S')
		rotate(game, M_PI / 2);
	else if (game->map->player == 'N')
		rotate(game, M_PI * 1.5);
	else if (game->map->player == 'W')
		rotate(game, M_PI);
}

void	run_game(t_game *game)
{
	t_textures	textures;

	game->textures = &textures;
	game->mlx = initialise_mlx(game->mlx, game->arena);
}

void	key_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
	}
	rayhook(game);
}

int main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_arena		*arena;

	arena = create_arena(CAPACITY);
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	game.map = &map; // init game values in separate function?
	game.arena = arena;
	check_args(argc, argv[1], &game);
	check_map(argv[1], &game, arena);
	run_game(&game);
	init_game(&game);//needs to happen after map parsing, player SNWE set
	initialise_images(&game);
	rayhook(&game);
	mlx_key_hook(game.mlx, &key_input, &game);
	//mlx_loop_hook(game.mlx, &rayhook, &game);
	//mlx_loop_hook(game.mlx, &keyhook, &game);
	mlx_loop(game.mlx);
	//delete_textures(&game);
	mlx_terminate(game.mlx);
	clean_arena(arena);
	return (0);
}
