/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:11:49 by lguillen          #+#    #+#             */
/*   Updated: 2025/07/10 12:27:37 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(int num, t_game *game)
{
	if (num == 1)
		ft_putstr_fd("\033[91mError\nInitialising failed😤😤🥺\n\033[0m", 2);
	else if (num == 2)
		ft_putstr_fd("\033[91mError\nExtra players!👯‍♀️\n\033[0m", 2);
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
	else if (num == 8)
		ft_putstr_fd("\033[91mError\nMLX initialisation failed\n\033[0m", 2);
	else if (num == 9)
		ft_putstr_fd("\033[91mError\nfailed to open map file 🥺🥺\n\033[0m", 2);
	clean_arena(game->arena);
	delete_textures(game->textures);
	if (game->mlx)
		mlx_terminate(game->mlx);
	exit(EXIT_FAILURE);
}

void	ft_error_graphics(t_game *game)
{
	ft_putstr_fd("\033[91mError\nGraphics failed🔮😤🥺\n\033[0m", 2);
	delete_textures(game->textures);
	if (game->mlx)
		mlx_terminate(game->mlx);
	clean_arena(game->arena);
	exit(EXIT_FAILURE);
}
