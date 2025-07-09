#include "cub3d.h"
#include <stdio.h>

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
	// 'M' vois togglaa minimapin nakyviin
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
	mlx_key_hook(game->mlx, key_input, game);
	mlx_loop_hook(game->mlx, update_view, game);
	mlx_loop(game->mlx);
}

int main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_arena		*arena;

	arena = create_arena(CAPACITY);
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	game.map = &map;
	game.arena = arena;
	check_args(argc, argv[1], &game);
	check_map(argv[1], &game, arena);
	init_struct(&game);
	run_game(&game);
	//delete_textures(&game);
	mlx_terminate(game.mlx);//
	clean_arena(arena);//
	return (0);
}

