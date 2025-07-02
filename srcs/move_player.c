#include "cub3d.h"

// static void	clear_player(t_game *game)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	mlx_delete_image(game->mlx, game->minimap->player);
// 	game->minimap->player = mlx_new_image(game->mlx, MAX_W / 2, MAX_H / 2);
// 	while (y < game->minimap->tile_size)
// 	{
// 		x = 0;
// 		while (x < game->minimap->tile_size)
// 		{
// 			mlx_put_pixel(game->minimap->player, x, y, 0x00000000);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	update_minimap(t_game *game)
// {
// 	int	px;
// 	int	py;
// 	int	radius;

// 	px = (int)(game->map->player_pos.x * game->minimap->tile_size);
// 	py = (int)(game->map->player_pos.y * game->minimap->tile_size);
// 	radius = game->minimap->tile_size / 4;
// 	//clear_player(game);
// 	draw_player(game);
// }

void	move_player(t_game *game, char axis, int dir)
{
	double speed = 0.1;

	if (axis == 'x')
		game->minimap->player->instances->x += dir * speed;
	else if (axis == 'y')
		game->minimap->player->instances->y += dir * speed;
	//update_minimap(game);
}
