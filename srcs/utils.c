#include "cub3d.h"

void	ft_error(int num, t_game *game)
{
    if (num == 1)
        ft_putstr_fd("\033[91mError\nInitialising failed😤😤🥺\n\033[0m", 2);
    else if (num == 2)
        ft_putstr_fd("\033[91mError\nExtra players! It's not a co-op\n\033[0m", 2);
    else if (num == 3)
        ft_putstr_fd("\033[91mError\nCan't play with no players😔\n\033[0m", 2);
    else if (num == 4)
        ft_putstr_fd("\033[91mError\nUnknown character found!!!👽\n\033[0m", 2);
    else if (num == 5)
        ft_putstr_fd("\033[91mError\nMemory allocation failure💀💀\n\033[0m", 2);
    else if (num == 6)
        ft_putstr_fd("\033[91mError\nYour map's not valid💅\n\033[0m", 2);
    else if (num == 7)
        ft_putstr_fd("\033[91mError\nInvalid identifiers🧭\n\033[0m", 2);
    clean_arena(game->arena);
    exit(EXIT_FAILURE);
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
