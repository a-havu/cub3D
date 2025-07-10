#include "cub3d.h"

void	init_minimap_values(t_game *game)
{
	game->minimap->tile_size = TILE_SIZE;
	if (game->map->height > 20)
	{
		game->minimap->scale_factor = (float)20 / (float)(game->map->height);
		game->minimap->tile_size = game->minimap->tile_size * game->minimap->scale_factor;
	}
	game->minimap->map = mlx_new_image(game->mlx, MAX_W / 2, MAX_H / 2);
	if (!game->minimap->map)
		ft_error_graphics(game);
}

void	draw_minimap_loop(t_game *game, int y, int x)
{
	int	t_x;
	int	t_y;

	t_y = 0;
	while (t_y < game->minimap->tile_size)
	{
		t_x = 0;
		while (t_x < game->minimap->tile_size)
		{
			mlx_put_pixel(game->minimap->map,
				x * game->minimap->tile_size + t_x,
				y * game->minimap->tile_size + t_y, game->minimap->colour);
			t_x++;
		}
		t_y++;
	}
}

void	init_player(t_game *game)
{
	if (game->minimap->player)
		mlx_delete_image(game->mlx, game->minimap->player);
	game->minimap->player = mlx_new_image(game->mlx, MAX_W / 2, MAX_H / 2);
	if (!game->minimap->player)
		ft_error_graphics(game);
}
