#include "cub3d.h"

/* Get colour represented by 4-byte integers for red, green, 
and blue channels and alpha channel to represent transparency.
Sets each channels byte and combines into a single integer. */

int get_colour(int r, int g, int b)
{
    return(r << 24 | g << 16 | b << 8 | 255);
}

void	initialise_images(t_game *game)
{
    game->textures = arena_alloc(game->arena, sizeof(t_textures));
    game->textures->n_wall = mlx_load_png(game->map->no_wall);
    if (!game->textures->n_wall)
        ft_error(8, game);
    game->textures->s_wall = mlx_load_png(game->map->so_wall);
    if (!game->textures->s_wall)
        ft_error(8, game);
    game->textures->e_wall = mlx_load_png(game->map->ea_wall);
    if (!game->textures->e_wall)
        ft_error(8, game);
    game->textures->w_wall = mlx_load_png(game->map->we_wall);
    if (!game->textures->w_wall)
        ft_error(8, game);
    game->images.screen = mlx_new_image(game->mlx, MAX_W, MAX_H);//
    if (!game->images.screen)    
        ft_error(8, game);
    if (mlx_image_to_window(game->mlx, game->images.screen, 0, 0) == -1)
        ft_error(8, game);
}
