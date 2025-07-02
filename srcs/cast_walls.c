#include "cub3d.h"

/* 
tex_num: the value oh the current map square - 1

wall_x: represents the exact value where the wall was hit, tells which x-coordinate
of the texture to use. Can be y-coordinate of the wall, if side is 1, but always x of tex.

tex.x/y: coordinates of the texture. tex.y is calculated increased by step size

tex_w/h: width and height of texture

incr: the step with which tex.y is calculated (increment)
*/

/* moving the pixel pointer forward, calculating how many pixels to skip (x, y, width)
and multiplying by size of unsigned int to turn pixel number into bytes to skip */

/** Gets colour of the pixel
 * @param wall the wall that was hit
 * @param x the x-coordinate we are at
 * @param y the y-coordinate corresponding to the x
 */

static unsigned get_pixel_colour(mlx_texture_t *wall, unsigned x, unsigned y)
{
    unsigned    *colour;

    colour = (unsigned *)(wall->pixels + ((x + y * wall->width) * sizeof(unsigned)));
    return (*colour);
}

/** Calculates which part of the wall was hit and finds the x coordinate of that texture
 * @param game the game struct
 * @param wall the wall that was hit (nesw)
*/
static void    get_texture(t_game *game, mlx_texture_t *wall)
{    
    game->tex_h = wall->height;//set height and width of wall texture?
    game->tex_w = wall->width;
    game->tex_num = game->map->array[game->sqr.y][game->sqr.x] - 1;
    if (game->side == 0) //EW
        game->wall_x = game->map->plr_pos.y + game->wall_dist * game->raydir.y;
    else
        game->wall_x = game->map->plr_pos.y + game->wall_dist * game->raydir.x;
    game->wall_x -= floor(game->wall_x); //floor rounds a float to the nearest integer that <= it
    game->tex.x = (int)(game->wall_x * (double)game->tex_w);
    if (game->side == 0 && game->raydir.x > 0) //EW
        game->tex.x = game->tex_w - game->tex.x - 1;
    if (game->side == 1 && game->raydir.x < 0) //NS
        game->tex.x = game->tex_w - game->tex.x - 1;
    game->incr = 1.0 * game->tex_h / game->line_height;
    game->tex_pos = (game->draw_start - MAX_H / 2 + game->line_height / 2) * game->incr;
}

/** Draws the wall pixel by pixel in vertical stripes.
 * @param game t_game struct
 * @param x the x-coordinate we are at
 * @param wall the texture of the wall that was hit
 */
static void    draw_wall(t_game *game, unsigned x, mlx_texture_t *wall)
{
    int        y;
    unsigned   colour;

    y = game->draw_start;
    //draw ceiling
    while (y < game->draw_end)
    {
        game->tex.y = (int)game->tex_pos;
        //jos tex.y >= (int)wall height, tex.y = tex_h -1?
        game->tex_pos += game->incr;
        colour = get_pixel_colour(wall, game->tex.x, game->tex.y);
        printf("colour: %u\n", colour);
        mlx_put_pixel(game->images.screen, x, y, colour);
        y++;
    }
    //draw floor
}

/** Checks which side of a wall the vision hits and draws it accordingly
 * @param game t_game struct
 * @param x which x-coordinate we are at
 */
void    check_side(t_game *game, int x)
{
    if (game->side == 0 && game->step.x < 0) //check which wall hit and from which side
    {
        get_texture(game, game->textures->e_wall);
        draw_wall(game, x, game->textures->e_wall);
    }
    if (game->side == 0 && game->step.x > 0)
    {
        get_texture(game, game->textures->w_wall);
        draw_wall(game, x, game->textures->w_wall);
    }
    if (game->side == 1 && game->step.x < 0)
    {
        get_texture(game, game->textures->n_wall);
        draw_wall(game, x, game->textures->n_wall);
    }
    if (game->side == 1 && game->step.x > 0)
    {
        get_texture(game, game->textures->s_wall);
        draw_wall(game, x, game->textures->s_wall);
    }
}
