#include "cub3d.h"

static void	validate_identifiers(t_game *game)
{
	if (game->map->no > 1 || game->map->so > 1
		|| game->map->we > 1 || game->map->ea > 1
		|| game->map->f > 1 || game->map->c > 1)
		{
			ft_putstr_fd("\033[91mError\nInvalid identifiers🧭\n\033[0m", 2);
			clean_arena(game->arena);
			exit(EXIT_FAILURE);
		}
	if (game->map->no == 0 || game->map->so == 0
		|| game->map->we == 0 || game->map->ea == 0
		|| game->map->f == 0 || game->map->c == 0)
		{
			ft_putstr_fd("\033[91mError\nInvalid identifiers🧭\n\033[0m", 2);
			clean_arena(game->arena);
			exit(EXIT_FAILURE);
		}
}

void	find_identifiers(char **elements, t_game *game)
{
	int	i;

	i = 0;
	while(i <= 11)
	{
		if (i % 2 == 0)
		{
			if (!ft_strncmp(elements[i], "NO", 3))
			{
				game->map->no++;
				game->map->no_wall = elements[i + 1];
			}
			else if (!ft_strncmp(elements[i], "SO", 3))
			{
				game->map->so++;
				game->map->so_wall = elements[i + 1];
			}
			else if (!ft_strncmp(elements[i], "WE", 3))
			{
				game->map->we++;
				game->map->we_wall = elements[i + 1];
			}
			else if (!ft_strncmp(elements[i], "EA", 3))
			{
				game->map->ea++;
				game->map->ea_wall = elements[i + 1];
			}
			else if (!ft_strncmp(elements[i], "F", 3))
			{
				game->map->f++;
				game->map->f_value = elements[i + 1];
			}
			else if (!ft_strncmp(elements[i], "C", 3))
			{
				game->map->c++;
				game->map->c_value = elements[i + 1];
			}
			else
				ft_error(7, game);
		}
		i++;
	}
	validate_identifiers(game);
	game->map->last_identifier = arena_join(game->arena, elements[i - 2], " ");
	if (!game->map->last_identifier)
		ft_error(5, game);
	game->map->last_identifier = arena_join(game->arena, game->map->last_identifier, elements[i - 1]);
	if (!game->map->last_identifier)
		ft_error(5, game);
	game->map->last_id = i / 2;
}

bool	is_identifier(char *element)
{
	if (!ft_strncmp(element, "NO", 3))
		return (true);
	else if (!ft_strncmp(element, "SO", 3))
		return (true);
	else if (!ft_strncmp(element, "WE", 3))
		return (true);
	else if (!ft_strncmp(element, "EA", 3))
		return (true);
	else if (!ft_strncmp(element, "F", 3))
		return (true);
	else if (!ft_strncmp(element, "C", 3))
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

void	count_symbols(t_game *game)
{
	int	x;
	int	y;

	y = 0;
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
					{
						game->map->player_count++;
						game->map->player = game->final_map[y][x];
						game->map->player_pos.y = y;
						game->map->player_pos.x = x;
					}
			else if (game->final_map[y][x] != '0'
				&& game->final_map[y][x] != '1'
				&& game->final_map[y][x] != '\n')
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
