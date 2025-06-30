#include "cub3d.h"

/* 
tex_num: the value oh the current map square - 1

wall_x: represents the exact value where the wall was hit, tells which x-coordinate
of the texture to use. Can be y-coordinate of the wall, if side is 1, but always x of tex.
*/

static void    get_texture(t_game *game)
{
    //set height and width of wall texture?
    game->tex_num = game->map->array[game->map.y][game->map.x] - 1;
    if (game->side == 0) //EW
        game->wall_x = game->map->plr_pos.y + game->wall_dist * game->raydir.y;
    else
        game->wall_x = game->map->plr_pos.y + game->wall_dist * game->raydir.x;
}

void    check_side(t_game *game, int x)
{
    if (game->side == 0 && game->step.x < 0) //check which wall hit and from which side
    {
        //get texture --> mlx textures are structs with height & width, need to set these?
        //draw east wall
    }
    if (game->side == 0 && game->step.x > 0)
    {
        //get texture
        //draw west wall
    }
    if (game->side == 1 && game->step.x < 0)
    {
        //get texture
        //draw north wall
    }
    if (game->side == 1 && game->step.x > 0)
    {
        //get texture
        //draw south wall
    }
}