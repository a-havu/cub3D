#include "cub3d.h"
#include <stdio.h>

void	load_images(t_game *game)
{
	game->textures = arena_alloc(game->arena, sizeof(t_textures));
	if (!game->textures)
		ft_error(5, game);
	game->textures->n_wall = mlx_load_png(game->map->no_wall);
	game->textures->s_wall = mlx_load_png(game->map->so_wall);
	game->textures->e_wall = mlx_load_png(game->map->ea_wall);
	game->textures->w_wall = mlx_load_png(game->map->we_wall);
	//and the rest of them
	if (!game->textures->n_wall || !game->textures->s_wall
		|| !game->textures->e_wall || !game->textures->w_wall) //and the rest of them
		ft_error_graphics(game);
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
		move_player(game, 'y', UP);
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 'x', LEFT);
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 'y', DOWN);
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 'x', RIGHT);
	// else if (keydata.key == MLX_KEY_LEFT
	// 	&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// 	//move POV to left
	// else if (keydata.key == MLX_KEY_RIGHT 
	// 	&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
	// //	move POV to right
	// 'M' vois togglaa minimapin nakyviin
}

void	run_game(t_game *game)
{
	game->mlx = mlx_init(MAX_W, MAX_H, "SWEN THE BUGBOI", true);
	if (!game->mlx)
		ft_error(8, game);
	game->minimap = arena_alloc(game->arena, sizeof(t_minimap));
	if (!game->minimap)
		ft_error(8, game);
	game->minimap->tile_size = 50;
	load_images(game);
	place_minimap(game);
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
	game.map = &map; // create a set game info function for next 5 lines
	game.arena = arena;
	check_args(argc, argv[1], &game);
	check_map(argv[1], &game, arena);
	run_game(&game);
	// clean_arena(arena);
	// return (0); exit happens in run_game?
}
