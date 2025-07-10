/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguillen <lguillen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:13:36 by lguillen          #+#    #+#             */
/*   Updated: 2025/07/10 12:13:37 by lguillen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_identifier(char *element)
{
	if (!ft_strncmp(element, "NO ", 3))
		return (true);
	else if (!ft_strncmp(element, "SO ", 3))
		return (true);
	else if (!ft_strncmp(element, "WE ", 3))
		return (true);
	else if (!ft_strncmp(element, "EA ", 3))
		return (true);
	else if (!ft_strncmp(element, "F ", 2))
		return (true);
	else if (!ft_strncmp(element, "C ", 2))
		return (true);
	return (false);
}

void	check_args(int argc, char *arg, t_game *game)
{
	if (argc != 2 || ft_strlen(arg) < 5)
	{
		ft_putstr_fd("\033[91mError\nInvalid argument!☝️\n\033[0m", 2);
		clean_arena(game->arena);
		exit(EXIT_FAILURE);
	}
	if (open(arg, O_RDONLY) == -1)
	{
		ft_putstr_fd("\033[91mError\nYour map's not valid💅\n\033[0m", 2);
		clean_arena(game->arena);
		exit(EXIT_FAILURE);
	}
}

static void	set_player_info(t_game *game, int y, int x)
{
	game->map->player_count++;
	game->map->player = game->final_map[y][x];
	game->map->plr_pos.y = y + 0.5;
	game->map->plr_pos.x = x + 0.5;
	game->final_map[y][x] = '0';
}

void	count_symbols(t_game *game, int y, int x)
{
	while (game->final_map[y])
	{
		x = 0;
		while (game->final_map[y][x])
		{
			if (game->final_map[y][x] == ' ')
				game->final_map[y][x] = '1';
			if (game->final_map[y][x] == 'N' || game->final_map[y][x] == 'S'
					|| game->final_map[y][x] == 'E'
					|| game->final_map[y][x] == 'W')
				set_player_info(game, y, x);
			else if (game->final_map[y][x] != '0'
				&& game->final_map[y][x] != '1')
				ft_error(4, game);
			x++;
		}
		y++;
	}
	if (game->map->player_count > 1)
		ft_error(2, game);
	else if (game->map->player_count == 0)
		ft_error(3, game);
}
