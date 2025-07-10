/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:11:58 by lguillen          #+#    #+#             */
/*   Updated: 2025/07/10 13:02:45 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/** Transforms rgb representation into a colour 
* @param r	4 byte integer representing red
* @param r  4 byte integer representing green
* @param r  4 byte integer representing blue
*/
uint32_t	get_colour(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

/** Loads the necessary textures and images
* @param game	the game struct
*/
void	initialise_images(t_game *game)
{
	game->textures = arena_alloc(game->arena, sizeof(t_textures));
	if (!game->textures)
		ft_error(5, game);
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
}

/** Deletes all structs that have been previously loaded
* @param textures	the struct holding all textures
*/
void	delete_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->n_wall)
		mlx_delete_texture(textures->n_wall);
	if (textures->s_wall)
		mlx_delete_texture(textures->s_wall);
	if (textures->e_wall)
		mlx_delete_texture(textures->e_wall);
	if (textures->w_wall)
		mlx_delete_texture(textures->w_wall);
}
