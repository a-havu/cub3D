#include "../incl/cub3d.h"

void	find_identifiers(char **elements, t_game *game)
{
	int	i;

	i = 0;
	while(elements[i])
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
		i++;
	}
	if (game->map->no > 1 || game->map->so > 1
		|| game->map->we > 1 || game->map->ea > 1)
		ft_error(6, game);
	if (game->map->no == 0 || game->map->so == 0
		|| game->map->we == 0 || game->map->ea == 0)
		ft_error(6, game);
	// if there are invalid extra identifiers, ft_error
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

char    *sl_strjoin(char *s1, char const *s2)
{
    int        len_s1;
    int        len_s2;
    int        total_len;

    len_s1 = ft_strlen(s1);
    len_s2 = ft_strlen(s2);
    total_len = len_s1 + len_s2;
    ft_memcpy((s1 + len_s1), s2, len_s2);
    s1[total_len] = '\0';
    return (s1);
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
