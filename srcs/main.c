#include "cub3d.h"
#include <stdio.h>

/** Rotates raycasting values according to player orientation
 * @param game	the game struct
 * @param rot	by how much we rotate player's view
 */
void rotate(t_game *game, double rot)
{
    double olddir_x;
    double olddir_y;
    double oldpl_x;
    double oldpl_y;

    olddir_x = game->dir.x;
    olddir_y = game->dir.y;
    oldpl_x = game->plane.x;
    oldpl_y = game->plane.y;
	game->dir.x   = olddir_x * cos(rot) - olddir_y * sin(rot);
    game->dir.y   = olddir_x * sin(rot) + olddir_y * cos(rot);
    game->plane.x = oldpl_x * cos(rot) - oldpl_y * sin(rot);
    game->plane.y = oldpl_x * sin(rot) + oldpl_y * cos(rot);
}

/** Sets raycasting values in game struct
 * @param game the game struct
 */
void	init_struct(t_game *game)
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

void	key_input(mlx_key_data_t keydata, void *param)
{
	t_game *game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		//clean_arena(game->arena);//taa crashaa
		exit(EXIT_SUCCESS);
	}
	else if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		update_raycast(game, 'y', UP);
		move_player(game, 'y', UP);
	}
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		update_raycast(game, 'x', LEFT);
		move_player(game, 'x', LEFT);
	}
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		update_raycast(game, 'y', DOWN);
		move_player(game, 'y', DOWN);
	}
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	{
		update_raycast(game, 'x', RIGHT);
		move_player(game, 'x', RIGHT);
	}//
		else if (keydata.key == MLX_KEY_UP
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(game, 0.33);
	else if (keydata.key == MLX_KEY_LEFT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(game, (M_PI / 2) * 0.1);
	else if (keydata.key == MLX_KEY_DOWN
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(game, 0.33);
	else if (keydata.key == MLX_KEY_RIGHT
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		rotate(game, (M_PI * 1.5) * 0.2);
	// else if (keydata.key == MLX_KEY_LEFT
	// 	&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// 	//move POV to left
	// else if (keydata.key == MLX_KEY_RIGHT 
	// 	&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// //	move POV to right
	// 'M' vois togglaa minimapin nakyviin
	rayhook(game);
}

void	run_game(t_game *game)
{
	t_textures    textures;

	game->textures = &textures;
	game->mlx = initialise_mlx(game);
	game->minimap = arena_alloc(game->arena, sizeof(t_minimap));
	if (!game->minimap)
		ft_error(8, game);
	game->minimap->tile_size = 50;
	initialise_images(game);
	place_minimap(game);
	rayhook(game);
	mlx_key_hook(game->mlx, key_input, game);
	// mlx_loop_hook(game.mlx, &rayhook, &game);
	mlx_loop(game->mlx);
	// mlx_terminate(game->mlx);
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
	init_struct(&game);//needs to happen after map parsing, player SNWE set
	run_game(&game);
	//delete_textures(&game);
	mlx_terminate(game.mlx);
	clean_arena(arena);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	t_game		game;
// 	t_map		map;
// 	t_arena		*arena;

// 	arena = create_arena(CAPACITY);
// 	ft_memset(&game, 0, sizeof(t_game));
// 	ft_memset(&map, 0, sizeof(t_map));
// 	game.map = &map; // create a set game info function for next 5 lines
// 	game.arena = arena;
// 	check_args(argc, argv[1], &game);
// 	check_map(argv[1], &game, arena);
// 	run_game(&game);
// 	// clean_arena(arena);
// 	// return (0); exit happens in run_game?
// }
