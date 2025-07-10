/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:12:07 by lguillen          #+#    #+#             */
/*   Updated: 2025/07/10 12:23:18 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_t	*initialise_mlx(t_game *game)
{
	game->mlx = mlx_init(MAX_W, MAX_H, "SWEN THE BUGBOI", false);
	if (!game->mlx)
		ft_error(8, game);
	return (game->mlx);
}

/** Sets raycasting values in game struct
 * @param game the game struct
 */
void	init_struct(t_game *game)
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
