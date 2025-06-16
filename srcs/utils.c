#include "cub3d.h"

void	exit_process(t_map *map)
{
	(void)map;//
	//if (map->array != NULL)
	//	free_arr(map->array);
	//whatever needs to be freed
	//can also send a msg to this function to print what went wrong?
	exit(1); //or send a code and exit with exit(code);
}

void	img_error(t_game *game, char signal)
{
	delete_textures(game);
	mlx_terminate(game->mlx);
	if (signal == 't')
		exit_process(game->map);
	else if (signal == 'i')
		exit_process(game->map);
}

void	delete_textures(t_game *game)
{
	if (game->textures->n_wall)
		mlx_delete_texture(game->textures->n_wall);
	if (game->textures->e_wall)
		mlx_delete_texture(game->textures->e_wall);
	if (game->textures->s_wall)
		mlx_delete_texture(game->textures->s_wall);
	if (game->textures->w_wall)
		mlx_delete_texture(game->textures->w_wall);
	if (game->textures->door)
		mlx_delete_texture(game->textures->door);
	if (game->textures->camera)
		mlx_delete_texture(game->textures->camera);
	if (game->textures->insect1)
		mlx_delete_texture(game->textures->insect1);
	if (game->textures->insect2)
		mlx_delete_texture(game->textures->insect2);
	if (game->textures->insect3)
		mlx_delete_texture(game->textures->insect3);
	if (game->textures->insect4)
		mlx_delete_texture(game->textures->insect4);
}
