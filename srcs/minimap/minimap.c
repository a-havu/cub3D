#include "cub3d.h"

void	draw_player(t_game *game)
{
	int			radius;
	double		px;
	double		py;
	int			y;
	int			x;
	
	init_player(game);
	px = game->map->plr_pos.x * game->minimap->tile_size;
	py = game->map->plr_pos.y * game->minimap->tile_size;
	radius = game->minimap->tile_size / 4;
	y = -radius;
	while(y <= radius)
	{
		x = -radius;
		while(x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				mlx_put_pixel(game->minimap->player, px + x, py + y, 0xFF0000FF);
			x++;
		}
		y++;
	}
	if (mlx_image_to_window(game->mlx, game->minimap->player, 0, 0) < 0)
		ft_error_graphics(game);
}

void	place_minimap(t_game *game)
{
	int			x;
	int			y;
	
	y = 0;
	init_minimap_values(game);
	while(game->final_map[y])
	{
		x = 0;
		while(game->final_map[y][x])
		{
			if (game->final_map[y][x] == '0' || game->final_map[y][x] == 'N')
				game->minimap->colour = 0x894e97;
			else if (game->final_map[y][x] == '1')
				game->minimap->colour = 0x000000FF;
			draw_minimap_loop(game, y, x);
			x++;
		}
		y++;
	}
	if (mlx_image_to_window(game->mlx, game->minimap->map, 0, 0) < 0)
		ft_error_graphics(game);
	draw_player(game);
}
