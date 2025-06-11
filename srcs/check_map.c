#include "../incl/cub3d.h"

static void	convert_cub_to_array(t_game *game, int fd, int rows)
{
	char	*line;

	line = NULL;
	game->map->one_d_array = ft_calloc(rows + 1, sizeof(char *));
	if (!game->map->one_d_array)
		ft_error(1, game);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		game->map->one_d_array = ft_strjoin(game->map->one_d_array, line);
		if(!game->map->one_d_array)
			ft_error(5, game);
		free(line);
	}
}

static void	check_paths(t_game *game, char **elements)
{
	int	i;

	i = 0;
	while(elements[i])
	{
		if (is_identifier(elements[i]))
		{
			if (elements[i + 1] && !is_identifier(elements[i + 1]))
				i++;
			else
				ft_error(66, game); //invalid texture path
		}
		i++;
	}
}

static void	check_cub_elements(t_game *game, int fd)
{
	char	**elements;
	int i = 0;

	elements = ft_split_charset(game->map->one_d_array, " \n");//tabs?
	find_identifiers(elements, game);
	check_paths(game, elements);
	free_2d_arr(elements);
}

void	check_map(char *arg, t_game *game)
{
	int		fd;
	int		rows;

	rows = get_rows(arg, game);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		ft_error(8, game);
	convert_cub_to_array(game, fd, rows);
	check_cub_elements(game, fd); // check the NO, SO, WE, EA and the colours
	//copy the map to a separate map array
	close(fd);
}
