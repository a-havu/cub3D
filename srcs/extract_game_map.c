#include "cub3d.h"

static void	get_map_array(t_game *game, int fd)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	game->map->array = ft_calloc(game->map->height + 1, sizeof(char *));
	if (!game->map->array)
		ft_error(1, game);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		// if (ft_strchr(line, '\n'))
		// 	*ft_strchr(line, '\n') = '\0';
		if (ft_strlen(line) > game->map->width)
			game->map->width = ft_strlen(line);
		game->map->array[i] = line;
		i++;
	}
	game->map->array[i] = NULL;
}

void	extract_game_map(char *arg, t_game *game)
{
	int	i;
	int	fd;

	fd = open(arg, O_RDONLY);
	i = 0;
	game->map->height = get_rows(arg, game);
	get_map_array(game, fd);
	//find the last identifier that was stored in the struct -> start the map from there

}