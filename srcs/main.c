#include "cub3d.h"
#include <stdio.h>

void	key_input(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		//clean_arena(game->arena);//taa crashaa
		exit(EXIT_SUCCESS);
	}
	else if (keydata.key == MLX_KEY_W
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 'y', UP);
	else if (keydata.key == MLX_KEY_A
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 'x', LEFT);
	else if (keydata.key == MLX_KEY_S
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 'y', DOWN);
	else if (keydata.key == MLX_KEY_D
		&& (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
		move_player(game, 'x', RIGHT);
	// 'M' vois togglaa minimapin nakyviin
}

/** Rotates raycasting values according to player orientation
 * @param game    the game struct
 * @param rot    by how much we rotate player's view
 */
void	rotate(t_game *game, double rot)
{
	double odx = game->dir.x;
	double ody = game->dir.y;
	double opx = game->plane.x;
	double opy = game->plane.y;

	game->dir.x   = odx * cos(rot) - ody * sin(rot);
	game->dir.y   = odx * sin(rot) + ody * cos(rot);
	game->plane.x = opx * cos(rot) - opy * sin(rot);
	game->plane.y = opx * sin(rot) + opy * cos(rot);
}

/** Sets raycasting values in game struct
 * @param game the game struct
 */
static void    init_game_struct(t_game *game)
{
	game->dir.x = 1;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
	if (game->map->player == 'S')
		rotate(game, M_PI / 2);
	else if (game->map->player == 'N')
		rotate(game, M_PI * 1.5);
	else if (game->map->player == 'W')
		rotate(game, M_PI);
}

void	run_game(t_game *game)
{
	t_textures    textures;

	game->textures = &textures;
	game->mlx = initialise_mlx(game);
	game->minimap = arena_alloc(game->arena, sizeof(t_minimap));
	if (!game->minimap)
		ft_error(5, game);
	initialise_images(game);
	place_minimap(game);
	mlx_key_hook(game->mlx, key_input, game);
	mlx_loop_hook(game->mlx, update_view, game);
	mlx_loop(game->mlx);
}

int main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_arena		*arena;

	arena = create_arena(CAPACITY);
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	game.map = &map;
	game.arena = arena;
	check_args(argc, argv[1], &game);
	check_map(argv[1], &game, arena);
	init_game_struct(&game);
	run_game(&game);
    mlx_terminate(game.mlx);
    clean_arena(arena);
    return (0);//luultavasti redundant rivit run_gamen jalkeen?
}

void    update_raycast(t_game *game, char axis, int dir)
{
    double  speed;
    int     plr_x;
    int     plr_y;

    speed = 0.3;
    if (axis == 'x')
    {
        if (dir == LEFT)
        {
            plr_x = (int)game->map->plr_pos.x - game->dir.y * (speed + 0.01);
            plr_y = (int)game->map->plr_pos.y + game->dir.y * (speed + 0.01);
            if (game->final_map[(int)game->map->plr_pos.y][plr_x] != '1')
                game->map->plr_pos.x += game->dir.y * speed;
            if (game->final_map[plr_y][(int)game->map->plr_pos.x] != '1')
                game->map->plr_pos.y -= game->dir.x * speed;
        }
        else if (dir == RIGHT)
        {
            plr_x = (int)game->map->plr_pos.x - game->dir.y * (speed + 0.01);
            plr_y = (int)game->map->plr_pos.y + game->dir.x * (speed + 0.01);
            if (game->final_map[(int)game->map->plr_pos.y][plr_x] != '1')
                game->map->plr_pos.x -= game->dir.y * speed;
            if (game->final_map[plr_y][(int)game->map->plr_pos.x] != '1')
                game->map->plr_pos.y += game->dir.x * speed; 
        }
    }
	    else if (axis == 'y')
    {
        if (dir == UP)
        {
            plr_x = (int)game->map->plr_pos.x + game->dir.x * (speed + 0.01);
            plr_y = (int)game->map->plr_pos.y + game->dir.y * (speed + 0.01);
            if (game->final_map[(int)game->map->plr_pos.y][plr_x] != '1')
                game->map->plr_pos.x += game->dir.x * speed;
            if (game->final_map[plr_y][(int)game->map->plr_pos.x] != '1')
                game->map->plr_pos.y += game->dir.y * speed;
        }
        else if (dir == DOWN)
        {
            plr_x = (int)game->map->plr_pos.x - game->dir.x * (speed + 0.01);
            plr_y = (int)game->map->plr_pos.y - game->dir.y * (speed + 0.01);
            if (game->final_map[(int)game->map->plr_pos.y][plr_x] != '1')
                game->map->plr_pos.x -= game->dir.x * speed;
            if (game->final_map[plr_y][(int)game->map->plr_pos.x] != '1')
                game->map->plr_pos.y -= game->dir.y * speed;           
        }
    }
}

