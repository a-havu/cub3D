#include "cub3d.h"

static void	validate_identifiers(t_game *game)
{
	if (game->map->no > 1 || game->map->so > 1
		|| game->map->we > 1 || game->map->ea > 1
		|| game->map->f > 1 || game->map->c > 1)
	{
		ft_putstr_fd("\033[91mError\nToo many identifiers🧭\n\033[0m", 2);
		clean_arena(game->arena);
		exit(EXIT_FAILURE);
	}
	if (game->map->no == 0 || game->map->so == 0
		|| game->map->we == 0 || game->map->ea == 0
		|| game->map->f == 0 || game->map->c == 0)
	{
		ft_putstr_fd("\033[91mError\nMissing identifier/s🧭\n\033[0m", 2);
		clean_arena(game->arena);
		exit(EXIT_FAILURE);
	}
}

static bool	find_no_so_we(t_game *game, char **elements, int i)
{
	if (!ft_strncmp(elements[i], "NO", 3))
	{
		game->map->no++;
		game->map->no_wall = elements[i + 1];
		return (true);
	}
	else if (!ft_strncmp(elements[i], "SO", 3))
	{
		game->map->so++;
		game->map->so_wall = elements[i + 1];
		return (true);
	}
	else if (!ft_strncmp(elements[i], "WE", 3))
	{
		game->map->we++;
		game->map->we_wall = elements[i + 1];
		return (true);
	}
	return (false);
}

static bool	find_ea_f_c(t_game *game, char **elements, int i)
{
	if (!ft_strncmp(elements[i], "EA", 3))
	{
		game->map->ea++;
		game->map->ea_wall = elements[i + 1];
		return (true);
	}
	else if (!ft_strncmp(elements[i], "F", 3))
	{
		game->map->f++;
		game->map->f_value = elements[i + 1];
		return (true);
	}
	else if (!ft_strncmp(elements[i], "C", 3))
	{
		game->map->c++;
		game->map->c_value = elements[i + 1];
		return (true);
	}
	return (false);
}

void	find_identifiers(char **elements, t_game *game)
{
	int	i;

	i = 0;
	while (i <= 11)
	{
		if (i % 2 == 0)
		{
			if (!find_no_so_we(game, elements, i))
			{
				if (!find_ea_f_c(game, elements, i))
					ft_error(7, game);
			}
		}
		i++;
	}
	validate_identifiers(game);
	game->map->last_identifier = arena_join(game->arena, elements[i - 2], " ");
	if (!game->map->last_identifier)
		ft_error(5, game);
	game->map->last_identifier = arena_join(game->arena,
			game->map->last_identifier, elements[i - 1]);
	if (!game->map->last_identifier)
		ft_error(5, game);
	game->map->last_id = i / 2;
}
