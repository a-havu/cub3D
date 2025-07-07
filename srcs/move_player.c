#include "cub3d.h"

void	move_player(t_game *game, char axis, int dir)
{
	double	speed = 10;
	// int		x;
	// int		y;

	// x = game->minimap->player->instances[0].x;
	// y = game->minimap->player->instances[0].y;
	if (axis == 'x')
		game->minimap->player->instances[0].x += dir * speed;
	else if (axis == 'y')
		game->minimap->player->instances[0].y += dir * speed;
	//update_minimap(game);
}
