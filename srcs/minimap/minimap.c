#include "cub3d.h"
#include <stdio.h>

void	draw_player(t_game *game)
{
	int	radius;
	int	px;
	int	py;
	int	y;
	int	x;
	
	game->minimap->player = mlx_new_image(game->mlx, MAX_W / 2, MAX_H / 2);
	// if (!game->minimap->player)
	// 	ft_error_graphics(game);
	px = (int)game->map->player_pos.x * game->minimap->tile_size;
	py = (int)game->map->player_pos.y * game->minimap->tile_size;
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
	mlx_image_to_window(game->mlx, game->minimap->player, 0, 0);
}

void	place_minimap(t_game *game)
{
	int			x;
	int			y;
	int			t_x;
	int			t_y;
	uint32_t	colour;

	y = 0;
	game->minimap->map = mlx_new_image(game->mlx, MAX_W / 2, MAX_H / 2);
	while(game->final_map[y])
	{
		x = 0;
		while(game->final_map[y][x])
		{
			if (game->final_map[y][x] == '0')
				colour = 0xFFFFFFFF;
			else if (game->final_map[y][x] == '1')
				colour = 0x000000FF;
			t_y = 0;
			while (t_y < game->minimap->tile_size)
			{
				t_x = 0;
				while (t_x < game->minimap->tile_size)
				{
					mlx_put_pixel(game->minimap->map,
						x * game->minimap->tile_size + t_x,
						y * game->minimap->tile_size + t_y, colour);
					t_x++;
				}
				t_y++;
			}
			x++;
		}
		y++;
	}
	mlx_image_to_window(game->mlx, game->minimap->map, 0, 0);
	draw_player(game);
}
