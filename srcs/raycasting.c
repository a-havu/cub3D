#include "cub3d.h"

/** Calculates the height of line to draw based on wall height
 * @param game the game struct
 */
static void	calc_wall_h(t_game *game)
{
	if (game->side == 0)
		game->wall_dist = (game->side_dist.x - game->delta.x);
	else
	{
		game->wall_dist = (game->side_dist.y - game->delta.y);
	}
	game->line_height = (int)(MAX_H / game->wall_dist);
	game->draw_start = -game->line_height / 2 + MAX_H / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + MAX_H / 2;
	if (game->draw_end >= MAX_H)
		game->draw_end = MAX_H - 1;
}

/** Performs the digital differential analysis to find where wall is hit.
 * @param game the game struct
*/
static void	perform_dda(t_game *game)
{
	game->hit = false;
	while (game->hit == false)
	{
		if (game->side_dist.x < game->side_dist.y)
		{
			game->side_dist.x += game->delta.x;
			game->sqr.x += game->step.x;
			game->side = 0;
		}
		else
		{
			game->side_dist.y += game->delta.y;
			game->sqr.y += game->step.y;
			game->side = 1;
		}
		if (game->final_map[game->sqr.y][game->sqr.x] == '1')
			game->hit = true;
	}
}

/** Calculates the distance the ray has to travel
 * @param game the game struct
 */
static void	calc_side_dist(t_game *g)
{
	if (g->raydir.x < 0)
	{
		g->step.x = -1;
		g->side_dist.x = (g->map->plr_pos.x - g->sqr.x) * g->delta.x;
	}
	else
	{
		g->step.x = 1;
		g->side_dist.x = (g->sqr.x + 1.0 - g->map->plr_pos.x) * g->delta.x;
	}
	if (g->raydir.y < 0)
	{
		g->step.y = -1;
		g->side_dist.y = (g->map->plr_pos.y - g->sqr.y) * g->delta.y;
	}
	else
	{
		g->step.y = 1;
		g->side_dist.y = (g->sqr.y + 1.0 - g->map->plr_pos.y) * g->delta.y;
	}
}

/** Calculates the direction of the ray and the distance to cross to next x/y
 * @param game  the game struct
 * @param x     the x-coordinate we are at on game window
 */
static void	calc_ray_n_delta(t_game *game, int x)
{
	game->camera_x = 2 * x / (double)MAX_W - 1;
	game->raydir.x = game->dir.x + game->plane.x * game->camera_x;
	game->raydir.y = game->dir.y + game->plane.y * game->camera_x;
	game->sqr.x = (int)game->map->plr_pos.x;
	game->sqr.y = (int)game->map->plr_pos.y;
	if (game->raydir.x == 0)
		game->delta.x = 1e30;
	else
		game->delta.x = fabs(1 / game->raydir.x);
	if (game->raydir.y == 0)
		game->delta.y = 1e30;
	else
		game->delta.y = fabs(1 / game->raydir.y);
}

/** The loop hook for raycasting
 * @param param the game struct
 */
void	raycasting(t_game *game)
{
	unsigned int	x;

	x = 0;
	draw_cf(game->screen, game);
	while (x < MAX_W)
	{
		calc_ray_n_delta(game, x);
		calc_side_dist(game);
		perform_dda(game);
		calc_wall_h(game);
		draw(game, x);
		x++;
	}
}
