#include "cub3d.h"

void    update_raycast(t_game *game, char axis, int dir)
{
    double  speed;;

    speed = 0.3;
    if (axis == 'x')
        game->map->plr_pos.x += dir * speed;
    else if (axis == 'y')
        game->map->plr_pos.y += dir * speed;
}
