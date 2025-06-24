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

void	rayhook(void *param)
{
	t_game	*game;
	int		x;

	game = param;
	x = 0;
	while (x < MAX_W) // screen width
	{
		game->camera.x = 2 * x / (double)MAX_W - 1; // screen width
		game->raydir.x = game->dir.x + game->plane.x * game->camera.x;
		game->raydir.y = game->dir.y + game->plane.y * game->camera.x;
		//game->map_x = (int)game->pos_x; check what is map_x and pos_x
		//game->map_y = (int)game->pos_y;
	}

	
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
	game.mlx = initialise_mlx(game.mlx, game.map);
	initialise_images(&game, &images);
	//mlx_key_hook(game.mlx, &key_input, &game);
	mlx_loop_hook(game.mlx, &rayhook, &game);
	//mlx_loop(game.mlx);
	delete_textures(&game);
	mlx_terminate(game.mlx);
	clean_arena(&arena);
	return (0);
}
