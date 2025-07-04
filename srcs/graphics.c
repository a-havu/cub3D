#include "cub3d.h"

/* Get colour represented by 4-byte integers for red, green, 
and blue channels and alpha channel to represent transparency.
Sets each channels byte and combines into a single integer. */

uint32_t get_colour(int r, int g, int b)
{
    return(r << 24 | g << 16 | b << 8 | 255);
}

// static int	**convert_texture_to_color_array(xpm_t *image)
// {
// 	int	**tab;
// 	int	count;
// 	int	i;
// 	int	j;

// 	tab = ft_calloc(sizeof(int *), image->texture.height + 1);
// 	count = 0;
// 	i = -1;
// 	while (++i < (int)image->texture.height)
// 	{	
// 		tab[i] = ft_calloc(sizeof(int), image->texture.width);
// 		j = -1;
// 		while (++j < (int)image->texture.width)
// 		{
// 			tab[i][j] = get_color(
// 					image->texture.pixels[count + 0],
// 					image->texture.pixels[count + 1],
// 					image->texture.pixels[count + 2],
// 					image->texture.pixels[count + 3]);
// 			count += 4;
// 		}
// 	}
// 	return (tab);
// }

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
    //game->e = convert_texture_to_color_array(xpm_t *image)
    game->images.screen = mlx_new_image(game->mlx, MAX_W, MAX_H);//
    if (!game->images.screen)    
        ft_error(8, game);
    if (mlx_image_to_window(game->mlx, game->images.screen, 0, 0) == -1)
        ft_error(8, game);
}
