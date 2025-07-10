/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:12:42 by lguillen          #+#    #+#             */
/*   Updated: 2025/07/10 12:12:44 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minimap_values(t_game *g)
{
	g->minimap->tile_size = TILE_SIZE;
	if (g->map->height > 20)
	{
		g->minimap->scale_fctr = (float)20 / (float)(g->map->height);
		g->minimap->tile_size = g->minimap->tile_size * g->minimap->scale_fctr;
	}
	g->minimap->map = mlx_new_image(g->mlx, MAX_W / 2, MAX_H / 2);
	if (!g->minimap->map)
		ft_error_graphics(g);
}

void	draw_minimap_loop(t_game *game, int y, int x)
{
	int	t_x;
	int	t_y;

	t_y = 0;
	while (t_y < game->minimap->tile_size)
	{
		t_x = 0;
		while (t_x < game->minimap->tile_size)
		{
			mlx_put_pixel(game->minimap->map,
				x * game->minimap->tile_size + t_x,
				y * game->minimap->tile_size + t_y, game->minimap->colour);
			t_x++;
		}
		t_y++;
	}
}

void	init_player(t_game *game)
{
	if (game->minimap->player)
		mlx_delete_image(game->mlx, game->minimap->player);
	game->minimap->player = mlx_new_image(game->mlx, MAX_W / 2, MAX_H / 2);
	if (!game->minimap->player)
		ft_error_graphics(game);
}
