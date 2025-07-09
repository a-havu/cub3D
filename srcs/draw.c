#include "cub3d.h"

/** Gets colour of the pixel
 * @param wall  the wall that was hit
 * @param x     the x-coordinate we are at
 * @param y     the y-coordinate corresponding to the x
 */

static uint32_t get_pixel_colour(mlx_texture_t *wall, uint32_t x, uint32_t y)
{
    uint8_t     *pixel;
    uint32_t    colour;

    pixel = wall->pixels + (y * wall->width + x) * 4;
    colour = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | (pixel[3]);
    return (colour);
}

/** Calculates which part of the wall was hit and finds the x coordinate of that texture
 * @param game the game struct
 * @param wall the wall that was hit (SWEN)
*/
static void    get_texture(t_game *game, mlx_texture_t *wall)
{    
    game->tex_h = wall->height;//set height and width of wall texture?
    game->tex_w = (double)wall->width;
    game->tex_num = game->final_map[game->sqr.y][game->sqr.x] - 1;
    if (game->side == 0) //EW
        game->wall_x = game->map->plr_pos.y + game->wall_dist * game->raydir.y;
    else
        game->wall_x = game->map->plr_pos.x + game->wall_dist * game->raydir.x;
    game->wall_x -= floor(game->wall_x); //floor rounds a float to the nearest integer that <= it
    game->tex.x = (int)(game->wall_x * game->tex_w);
    if (game->side == 0 && game->raydir.x < 0) //EW
        game->tex.x = game->tex_w - game->tex.x - 1;
    if (game->side == 1 && game->raydir.y > 0) //NS
        game->tex.x = game->tex_w - game->tex.x - 1;
    game->incr = 1.0 * game->tex_h / game->line_height;
    game->tex_pos = ((double)game->draw_start - (double)MAX_H / 2 + (double)game->line_height / 2) * game->incr;
}

/** Draws the wall pixel by pixel in vertical stripes.
 * @param game  t_game struct
 * @param x     the x-coordinate we are at
 * @param wall  the texture of the wall that was hit
 */
static void    draw_wall(t_game *game, unsigned x, mlx_texture_t *wall)
{
    int         y;
    unsigned    colour;

    y = game->draw_start;
    while (y < game->draw_end)
    {
        game->tex.y = (int)game->tex_pos;
        if (game->tex_pos > (int)wall->height - 1)
            game->tex_pos = wall->height - 1;
        game->tex_pos += game->incr;
        colour = get_pixel_colour(wall, game->tex.x, game->tex.y);
        mlx_put_pixel(game->images.screen, x, y, colour);
        y++;
    }
}

/** Checks which side of a wall the vision hits and draws it accordingly
 * @param game  t_game struct
 * @param x     which x-coordinate we are at
 */
void    draw(t_game *game, int x)
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
    if (game->side == 1 && game->step.y < 0)
    {
        get_texture(game, game->textures->n_wall);
        draw_wall(game, x, game->textures->n_wall);
    }
    if (game->side == 1 && game->step.y > 0)
    {
        get_texture(game, game->textures->s_wall);
        draw_wall(game, x, game->textures->s_wall);
    }
}

/** Draws the ceiling and floor according to the given colours.
 * @param screen the game window image
 * @param game the game struct
 */
void    draw_cf(mlx_image_t *screen, t_game *game)
{
    int y;
    int x;
    uint32_t    c_colour;
    uint32_t    f_colour;

    y = 0;
    f_colour = get_colour(game->floor[0], game->floor[1], game->floor[2]);
    c_colour = get_colour(game->ceiling[0], game->ceiling[1], game->ceiling[2]);
    while (y < MAX_H)
    {
        x = 0;
        while (x < MAX_W)
        {
            if (y < MAX_H / 2)
                mlx_put_pixel(screen, x, y, c_colour);
            else
                mlx_put_pixel(screen, x, y, f_colour);
            x++;
        }
       y++;
    }

}
