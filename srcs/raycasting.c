#include "cub3d.h"

/* iterate throught the width of the screen in pixels, x representing
the column you're currently at.

camera.x: tells where the current column lies on the projection plane
from -1 left, 0 centre, 1 right

dir.x/y: player's direction vector, base direction of vision

raydir.x/y: casts rays to find walls, direction of current ray for column x
the amount of units the ray goes in the y-direction when taking one step
in x direction and vice versa

plane.x/y: camera plane vector (perpedicular to dir, defines FOV)

sqr: which square of the map we're in

delta: the distance the ray has to travel to go from one x/y side to the next
eg. delta.x = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
What actually matters is the ratio of delta.x and delta.y so can be calculated
not with actual lengths of raydirs, hence use 1 instead of |raydir|
if raydir.x the ray is perfectly vertical and to avoid from division by 0,
delta is set to an arbitrarily large number 1e30 to represent infinite distance

step.x/y: stores whether to go in pos or neg direction, always -1 or 1.

side_dist.x/y: initially the distance the ray has to travel from its start position
to the first x/y side. Gets incremented as steps are taken.
If the ray dir has a negative value, side_dist is the distance from the ray starting
position to the first side to the left/above (x/y).
Calculate how far the player is from the relevant wall edge and scale it using delta
to get the real (diagonal) distance the ray travels

hit: boolean for has a wall been hit.

side: holds info wether x or y side of a wall was hit, x = 0, y = 1.

wall_dist: perpendicular wall distance from camera plane to avoid fisheye effect

line_height: by modifying what you multiply h with you an make taller or smaller walls.
Higher values create higher boxes.
*/

/** Calculates the height of line to draw on scree and lowest and highest pixel to fill in current stripe
 * @param game the game struct
 */
static void calc_wall_h(t_game *game)
{
    //printf("side dist: %f delta: %f\n", game->side_dist.x, game->delta.x);
	if (game->side == 0) //calc perpendicular distance TODO: instead of 0, EW or NS
        game->wall_dist = (game->side_dist.x - game->delta.x);
    else
	{
        game->wall_dist = (game->side_dist.y - game->delta.y);
	}
	//printf("wall dist: %f\n", game->wall_dist);
    game->line_height = (int)(MAX_H / game->wall_dist); // calc height
    game->draw_start = -game->line_height / 2 + MAX_H / 2;
    if (game->draw_start < 0)
        game->draw_start = 0;
    game->draw_end = game->line_height / 2 + MAX_H / 2; //shoud be height of screen
    if (game->draw_end >= MAX_H)
	{
        game->draw_end = MAX_H - 1;
	}
	//printf("wall_dist: %f | line_height: %d\n", game->wall_dist, game->line_height);
}

/** Performs the digital differential analysis to find where wall is hit.
 * @param game the game struct
*/

static void perform_dda(t_game *game)
{
    //int	steps = 0;
	game->hit = false;
	while (game->hit == false)
    {
        if (game->side_dist.x < game->side_dist.y)
        {
            game->side_dist.x += game->delta.x; // increments by delta distance
            game->sqr.x += game->step.x; //increments by one square
            game->side = 0;//EW Does it need to be E or W?
        }
        else
        {
            game->side_dist.y += game->delta.y;
            game->sqr.y += game->step.y;
            game->side = 1;//NS
        }
        if (game->final_map[game->sqr.y][game->sqr.x] == '1') //||door ||collectible
            game->hit = true;
    }
	//printf("DDA steps: %d\n", steps);
}

/** Calculates the distance the ray has to travel to the relevant wall edge and direction of step.
 * @param game the game struct
 */
static void calc_side_dist(t_game *game)
{
    if (game->raydir.x < 0) //calc step and initial side distance
	{
		game->step.x = -1;
		game->side_dist.x = (game->map->plr_pos.x - game->sqr.x) * game->delta.x;
	}
	else
	{
		game->step.x = 1;
		game->side_dist.x = (game->sqr.x + 1.0 - game->map->plr_pos.x) * game->delta.x;
	}
	if (game->raydir.y < 0)
	{
		game->step.y = -1;
		game->side_dist.y = (game->map->plr_pos.y - game->sqr.y) * game->delta.y;
	}
	else
	{
		game->step.y = 1;
		game->side_dist.y = (game->sqr.y + 1.0 - game->map->plr_pos.y) * game->delta.y;
	}
}

/** Calculates the direction of the ray and the distance the ray has to travel to cross to next x/y position
 * @param game the game struct
 * @param x the x-coordinate we are at on game window
 */
static void calc_ray_n_delta(t_game *game, int x)
{
    game->camera_x = 2 * x / (double)MAX_W - 1; // cal ray pos and dir
	game->raydir.x = game->dir.x + game->plane.x * game->camera_x;
	game->raydir.y = game->dir.y + game->plane.y * game->camera_x;
	game->sqr.x = (int)game->map->plr_pos.x; // update location on map
	game->sqr.y = (int)game->map->plr_pos.y;
    if (game->raydir.x == 0) //calc length of ray
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
void	raycasting(t_game *game)//void *param)
{
	//t_game			*game;
	unsigned int	x;

	//game = param;
	x = 0;
	draw_cf(game->images.screen, game);
	while (x < MAX_W) // screen width
	{
		calc_ray_n_delta(game, x);
        calc_side_dist(game);
        perform_dda(game);
        calc_wall_h(game);
        draw(game, x);
		x++;
	}
}

