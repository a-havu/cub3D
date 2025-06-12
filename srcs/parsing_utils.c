#include "../incl/cub3d.h"

static void	validate_identifiers(t_game *game)
{
	if (game->map->no > 1 || game->map->so > 1
		|| game->map->we > 1 || game->map->ea > 1
		|| game->map->f > 1 || game->map->c > 1)
		{
			ft_putstr_fd("\033[91mError\nInvalid identifiers🧭\n\033[0m", 2);
			free(game->map->one_d_array);
			exit(EXIT_FAILURE);
		}
	if (game->map->no == 0 || game->map->so == 0
		|| game->map->we == 0 || game->map->ea == 0
		|| game->map->f == 0 || game->map->c == 0)
		{
			ft_putstr_fd("\033[91mError\nInvalid identifiers🧭\n\033[0m", 2);
			free(game->map->one_d_array);
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
				game->map->no++;
			else if (!ft_strncmp(elements[i], "SO", 3))
				game->map->so++;
			else if (!ft_strncmp(elements[i], "WE", 3))
				game->map->we++;
			else if (!ft_strncmp(elements[i], "EA", 3))
				game->map->ea++;
			else if (!ft_strncmp(elements[i], "F", 3))
				game->map->f++;
			else if (!ft_strncmp(elements[i], "C", 3))
				game->map->c++;
			else
			{
				ft_putstr_fd("\033[91mError\nInvalid identifiers🧭\n\033[0m", 2);
				free(game->map->one_d_array);
				exit(EXIT_FAILURE);
			}
			game->map->i += ft_strlen(elements[i]);
		}
		i++;
		game->map->i += ft_strlen(elements[i]);
	}
	validate_identifiers(game);
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

int	get_rows(char *arg, t_game *game)
{
	int		fd;
	int		rows;
	char	*line;

	rows = 0;
	line = NULL;
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		ft_error(8, game);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		rows++;
		free(line);
	}
	close(fd);
	return (rows);
}
