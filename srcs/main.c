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

// void	hook(void *param)
// {
// 	t_game	*game;

// 	game = param;
	
// }

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

// void	hook(void *param)
// {
// 	t_game	*game;

// 	game = param;
	
// }

int main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_images	images;
	t_textures	textures;
	t_arena		*arena;

	arena = create_arena(CAPACITY);
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&textures, 0, sizeof(t_textures));
	game.map = &map; // create a set game info function for next 5 lines
	game.images = &images;
	game.textures = &textures;
	map.name = ft_strdup(argv[1]);//
	game.mlx = initialise_mlx(game.mlx, game.map);
	// mlx_key_hook(game.mlx, &key_input, &game);
	// mlx_loop_hook(game.mlx, &hook, &game);
	//mlx_loop_hook(game.mlx, &key_input, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	exit_process(&map);
	return (0);
}
