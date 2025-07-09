#include "cub3d.h"

void    update_raycast(t_game *game, char axis, int dir)
{
    double  speed;
    int     plr_x;
    int     plr_y;

    speed = 0.1;
    if (axis == 'x')
    {
        if (dir == LEFT)
        {
            plr_x = (int)(game->map->plr_pos.x + game->dir.y * (speed + 0.01));
            plr_y = (int)(game->map->plr_pos.y - game->dir.x * (speed + 0.01));
            if (game->final_map[(int)game->map->plr_pos.y][plr_x] == '0')
                game->map->plr_pos.x += game->dir.y * speed;
            if (game->final_map[plr_y][(int)game->map->plr_pos.x] == '0')
                game->map->plr_pos.y -= game->dir.x * speed;
        }
        else if (dir == RIGHT)
        {
            plr_x = (int)(game->map->plr_pos.x - game->dir.y * (speed + 0.01));
            plr_y = (int)(game->map->plr_pos.y + game->dir.x * (speed + 0.01));
            if (game->final_map[(int)game->map->plr_pos.y][plr_x] == '0')
                game->map->plr_pos.x -= game->dir.y * speed;
            if (game->final_map[plr_y][(int)game->map->plr_pos.x] == '0')
                game->map->plr_pos.y += game->dir.x * speed; 
        }
    }
    else if (axis == 'y')
    {
        if (dir == UP)
        {
            plr_x = (int)(game->map->plr_pos.x + game->dir.x * (speed + 0.01));
            plr_y = (int)(game->map->plr_pos.y + game->dir.y * (speed + 0.01));
            if (game->final_map[(int)game->map->plr_pos.y][plr_x] == '0')
                game->map->plr_pos.x += game->dir.x * speed;
            if (game->final_map[plr_y][(int)game->map->plr_pos.x] == '0')
                game->map->plr_pos.y += game->dir.y * speed;
        }
        else if (dir == DOWN)
        {
            plr_x = (int)(game->map->plr_pos.x - game->dir.x * (speed + 0.01));
            plr_y = (int)(game->map->plr_pos.y - game->dir.y * (speed + 0.01));
            if (game->final_map[(int)game->map->plr_pos.y][plr_x] == '0')
                game->map->plr_pos.x -= game->dir.x * speed;
            if (game->final_map[plr_y][(int)game->map->plr_pos.x] == '0')
                game->map->plr_pos.y -= game->dir.y * speed;           
        }
    }
}

/** Rotates raycasting values according to player orientation
 * @param game	the game struct
 * @param rot	by how much we rotate player's view
 */
void rotate(t_game *game, double rot)
{
    double olddir_x;
    double olddir_y;
    double oldpl_x;
    double oldpl_y;

    olddir_x = game->dir.x;
    olddir_y = game->dir.y;
    oldpl_x = game->plane.x;
    oldpl_y = game->plane.y;
	game->dir.x   = olddir_x * cos(rot) - olddir_y * sin(rot);
    game->dir.y   = olddir_x * sin(rot) + olddir_y * cos(rot);
    game->plane.x = oldpl_x * cos(rot) - oldpl_y * sin(rot);
    game->plane.y = oldpl_x * sin(rot) + oldpl_y * cos(rot);
}

/** Updates the game view based on key input
 * @param param the game struct
 */
void update_view(void *param)
{
    t_game *game = param;

    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
        update_raycast(game, 'y', UP);
		draw_player(game);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
        update_raycast(game, 'y', DOWN);
		draw_player(game);
	}
    else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
        update_raycast(game, 'x', LEFT);
		draw_player(game);
	}
    else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
        update_raycast(game, 'x', RIGHT);
		draw_player(game);
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))//tahan sitte se minimap FOV
	{
        rotate(game, -0.02);
	}
    if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
        rotate(game, 0.02);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(game->mlx);
		delete_textures(game->textures);
		clean_arena(game->arena);
		exit(EXIT_SUCCESS);
	}
    raycasting(game);
}
