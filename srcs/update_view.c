#include "cub3d.h"

/** Updates the player position based on movement
 * @param game  the game struct
 * @param speed the movement speed
 * @param dir   direction of movement
 */
static void	move_lr(t_game *game, double speed, int dir)
{
	int	plr_x;
	int	plr_y;

	if (dir == LEFT)
	{
		plr_x = (int)(game->map->plr_pos.x + game->dir.y * (speed));
		plr_y = (int)(game->map->plr_pos.y - game->dir.x * (speed));
		if (game->final_map[(int)game->map->plr_pos.y][plr_x] == '0')
			game->map->plr_pos.x += game->dir.y * speed;
		if (game->final_map[plr_y][(int)game->map->plr_pos.x] == '0')
			game->map->plr_pos.y -= game->dir.x * speed;
	}
	else if (dir == RIGHT)
	{
		plr_x = (int)(game->map->plr_pos.x - game->dir.y * (speed));
		plr_y = (int)(game->map->plr_pos.y + game->dir.x * (speed));
		if (game->final_map[(int)game->map->plr_pos.y][plr_x] == '0')
			game->map->plr_pos.x -= game->dir.y * speed;
		if (game->final_map[plr_y][(int)game->map->plr_pos.x] == '0')
			game->map->plr_pos.y += game->dir.x * speed;
	}
}

/** Updates the player position based on movement
 * @param game  the game struct
 * @param speed the movement speed
 * @param dir   direction of movement
 */
static void	move_ud(t_game *game, double speed, int dir)
{
	int	plr_x;
	int	plr_y;

	if (dir == UP)
	{
		plr_x = (int)(game->map->plr_pos.x + game->dir.x * (speed));
		plr_y = (int)(game->map->plr_pos.y + game->dir.y * (speed));
		if (game->final_map[(int)game->map->plr_pos.y][plr_x] == '0')
			game->map->plr_pos.x += game->dir.x * speed;
		if (game->final_map[plr_y][(int)game->map->plr_pos.x] == '0')
			game->map->plr_pos.y += game->dir.y * speed;
	}
	else if (dir == DOWN)
	{
		plr_x = (int)(game->map->plr_pos.x - game->dir.x * (speed));
		plr_y = (int)(game->map->plr_pos.y - game->dir.y * (speed));
		if (game->final_map[(int)game->map->plr_pos.y][plr_x] == '0')
			game->map->plr_pos.x -= game->dir.x * speed;
		if (game->final_map[plr_y][(int)game->map->plr_pos.x] == '0')
			game->map->plr_pos.y -= game->dir.y * speed;
	}
}

/** Updates the raycast according to which direction the player moved
 * @param game  the game struct
 * @param dir   the direction the player moved
 */
void	update_raycast(t_game *game, int dir)
{
	double	speed;

	speed = 0.1;
	if (dir == LEFT || dir == RIGHT)
		move_lr(game, speed, dir);
	else if (dir == UP || dir == DOWN)
		move_ud(game, speed, dir);
}

/** Updates the game view based on key input
 * @param param the game struct
 */
void	update_view(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		update_raycast(game, UP);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		update_raycast(game, DOWN);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		update_raycast(game, LEFT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		update_raycast(game, RIGHT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(game, -ROT);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(game, ROT);
	raycasting(game);
}
