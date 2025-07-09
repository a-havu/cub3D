#include "cub3d.h"

/* Get colour represented by 4-byte integers for red, green, 
and blue channels and alpha channel to represent transparency.
Sets each channels byte and combines into a single integer. */

uint32_t get_colour(int r, int g, int b)
{
    return(r << 24 | g << 16 | b << 8 | 255);
}

void	initialise_images(t_game *game)
{
    game->textures = arena_alloc(game->arena, sizeof(t_textures));
    game->textures->n_wall = mlx_load_png(game->map->no_wall);
    if (!game->textures->n_wall)
        ft_error_graphics(game);
    game->textures->s_wall = mlx_load_png(game->map->so_wall);
    if (!game->textures->s_wall)
        ft_error_graphics(game);
    game->textures->e_wall = mlx_load_png(game->map->ea_wall);
    if (!game->textures->e_wall)
        ft_error_graphics(game);
    game->textures->w_wall = mlx_load_png(game->map->we_wall);
    if (!game->textures->w_wall)
        ft_error_graphics(game);
    //game->e = convert_texture_to_color_array(xpm_t *image)
    game->images.screen = mlx_new_image(game->mlx, MAX_W, MAX_H);//
    if (!game->images.screen)    
        ft_error_graphics(game);
    if (mlx_image_to_window(game->mlx, game->images.screen, 0, 0) == -1)
        ft_error_graphics(game);
}

void	delete_textures(t_textures *textures)
{
	if (textures->n_wall)
		mlx_delete_texture(textures->n_wall);
	if (textures->s_wall)
	 	mlx_delete_texture(textures->s_wall);
	if (textures->e_wall)
		mlx_delete_texture(textures->e_wall);
	if (textures->w_wall)
	 	mlx_delete_texture(textures->w_wall);
}
