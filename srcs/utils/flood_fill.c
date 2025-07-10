/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:13:29 by lguillen          #+#    #+#             */
/*   Updated: 2025/07/10 12:13:30 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(t_game *game, int y, int x)
{
	game->map_cpy[y][x] = 'A';
	if (y <= 0)
		ft_error(6, game);
	if (y >= game->map->height - 1)
		ft_error(6, game);
	if (game->map_cpy[y][x - 1] != '1' && game->map_cpy[y][x - 1] != ' '
		&& game->map_cpy[y][x - 1] != 'A')
	{
		if (x - 1 < 0)
			ft_error(6, game);
		flood_fill(game, y, (x - 1));
	}
	if (game->map_cpy[y + 1][x] != '1' && game->map_cpy[y + 1][x] != ' '
		&& game->map_cpy[y + 1][x] != 'A')
		flood_fill(game, (y + 1), x);
	if (game->map_cpy[y][x + 1] != '1' && game->map_cpy[y][x + 1] != ' '
		&& game->map_cpy[y][x + 1] != 'A')
	{
		if (x + 1 >= ft_len(game->map_cpy[y]))
			ft_error(6, game);
		flood_fill(game, y, (x + 1));
	}
	if (game->map_cpy[y - 1][x] != '1' && game->map_cpy[y - 1][x] != ' '
		&& game->map_cpy[y - 1][x] != 'A')
		flood_fill(game, (y - 1), x);
}

void	execute_flood_fill(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y <= game->map->height)
	{
		x = 0;
		while (x < ft_len(game->map_cpy[y]))
		{
			if (game->map_cpy[y][x] != ' ' && game->map_cpy[y][x] != '\0'
				&& game->map_cpy[y][x] != '1' && game->map_cpy[y][x] != '\n')
				flood_fill(game, y, x);
			x++;
		}
		y++;
	}
}
