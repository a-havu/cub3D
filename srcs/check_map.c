#include "cub3d.h"

static void	convert_cub_to_one_d_array(t_game *game, int fd)
{
	char	*line;

	line = NULL;
	game->map->one_d_array = ft_calloc(1, sizeof(char *));
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

/* splitting the created 1D array to extract the elements (texture paths & colour codes)*/

static void	check_cub_elements(t_game *game)
{
	char	**elements;

	elements = ft_split_charset(game->map->one_d_array, " \n"); //tabs?
	if (!elements)
		ft_error(5, game);
	find_identifiers(elements, game);
}

void	check_map(char *arg, t_game *game)
{
	int		fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		ft_error(8, game);
	convert_cub_to_one_d_array(game, fd);
	check_cub_elements(game);
	extract_game_map(arg, game);
	close(fd);
}
