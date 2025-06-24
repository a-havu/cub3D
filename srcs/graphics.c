#include "cub3d.h"

/* Get colour represented by 4-byte integers for red, green, 
and blue channels and alpha channel to represent transparency.
Sets each channels byte and combines into a single integer. */

int get_colour(int r, int g, int b, int a)
{
    return(r << 24 | g << 16 | b << 8 | a);
}

void	initialise_images(t_game *game, t_images *images)
{
    game->textures->n_wall = mlx_load_png(game->map->no_wall);
    if (!game->textures->n_wall)
        ft_error(game, 8);
    game->textures->s_wall = mlx_load_png(game->map->so_wall);
    if (!game->textures->s_wall)
        ft_error(game, 8);
    game->textures->e_wall = mlx_load_png(game->map->ea_wall);
    if (!game->textures->e_wall)
        ft_error(game, 8);
    game->textures->w_wall = mlx_load_png(game->map->we_wall);
    if (!game->textures->w_wall)
        ft_error(game, 8);
}
