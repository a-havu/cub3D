#include "cub3d.h"

/** Rotates raycasting values according to player orientation
 * @param game	the game struct
 * @param rot	by how much we rotate player's view
 */
void	rotate(t_game *game, double rot)
{
	double	olddir_x;
	double	olddir_y;
	double	oldpl_x;
	double	oldpl_y;

	olddir_x = game->dir.x;
	olddir_y = game->dir.y;
	oldpl_x = game->plane.x;
	oldpl_y = game->plane.y;
	game->dir.x = olddir_x * cos(rot) - olddir_y * sin(rot);
	game->dir.y = olddir_x * sin(rot) + olddir_y * cos(rot);
	game->plane.x = oldpl_x * cos(rot) - oldpl_y * sin(rot);
	game->plane.y = oldpl_x * sin(rot) + oldpl_y * cos(rot);
}

void	init_game_struct(t_game *game)
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
	game->mlx = initialise_mlx(game);
	game->minimap = arena_alloc(game->arena, sizeof(t_minimap));
	if (!game->minimap)
		ft_error(5, game);
	initialise_images(game);
	place_minimap(game);
	mlx_loop_hook(game->mlx, update_view, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
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
	return (0);
}
