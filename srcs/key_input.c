#include "cub3d.h"

void	move(t_game *game, char dir, int new_pos)
{
	if (dir == 'v')
	{
		if (game->map->array[new_pos][game->map->plr_pos.x] != '1')
		{
			game->images->door->instances[0].y = new_pos * PXL;
			game->map->plr_pos.y = new_pos;
		}
	}
	else if (dir == 'h')
	{
		if (game->map->array[game->map->plr_pos.y][new_pos] != '1')
		{
			game->images->door->instances[0].x = new_pos * PXL;
			game->map->plr_pos.x = new_pos;
		}
	}
	//ft_printf("\nx: %i y: %i\n", game->map->plr_pos.x, game->map->plr_pos.y);//
}

void	key_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		new_pos;
	char	dir;

	game = param;
	new_pos = 0;
	dir = 'v';
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);
		if (keydata.key == MLX_KEY_UP)
			new_pos = game->map->plr_pos.y - 1;
		if (keydata.key == MLX_KEY_DOWN)
			new_pos = game->map->plr_pos.y + 1;
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_RIGHT)
		{
			dir = 'h';
			new_pos = game->map->plr_pos.x - 1;
			if (keydata.key == MLX_KEY_RIGHT)
				new_pos = game->map->plr_pos.x + 1;
		}
		move(game, dir, new_pos);
	}
}