#include "cub3d.h"
#include <stdio.h>

/** Sets raycasting values in game struct
 * @param game the game struct
 */
static void    init_game_struct(t_game *game)
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
	t_textures    textures;

	game->textures = &textures;
	game->mlx = initialise_mlx(game);
	game->minimap = arena_alloc(game->arena, sizeof(t_minimap));
	if (!game->minimap)
		ft_error(5, game);
	initialise_images(game);
	place_minimap(game);
	//mlx_key_hook(game->mlx, key_input, game);
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
	init_game_struct(&game);
	run_game(&game);
    mlx_terminate(game.mlx);
	delete_textures(game.textures);
    clean_arena(arena);
    return (0);//luultavasti redundant rivit run_gamen jalkeen?
}

