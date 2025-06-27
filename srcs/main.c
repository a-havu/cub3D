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
	t_arena		*arena;

	arena = create_arena(CAPACITY);
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	game.map = &map; // create a set game info function for next 5 lines
	game.arena = arena;
	check_args(argc, argv[1], &game);
	check_map(argv[1], &game, arena);
	//run_game(&game);
	// clean_arena(arena);
	// return (0); TODO: exit happens in run_game?
}
