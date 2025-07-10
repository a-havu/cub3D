#include "cub3d.h"

void	get_map_array(t_game *game, int fd, t_arena *arena)
{
	char	*line;
	int		i;

	i = 0;
	game->map->array = arena_alloc(arena,
			(game->map->height + 1 + sizeof(char *)));
	if (!game->map->array)
		ft_error(5, game);
	while (1)
	{
		line = arena_next_line(fd, arena);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		if (ft_strlen(line) > game->map->width)
			game->map->width = ft_strlen(line);
		game->map->array[i] = arena_strdup(arena, line);
		if (!game->map->array[i])
			ft_error(5, game);
		i++;
	}
	game->map->array[i] = NULL;
	close(fd);
}

static char	**copy_loop(t_game *game, char **copy, int y)
{
	int	i;

	i = 0;
	while (game->map->array[y])
	{
		if (game->map->array[y][0] != '\n')
		{
			copy[i] = arena_strdup(game->arena, game->map->array[y]);
			if (!copy[i])
				ft_error(5, game);
			y++;
			i++;
		}
		else
			y++;
	}
	copy[i] = NULL;
	game->map->height = i;
	return (copy);
}

char	**copy_map(t_game *game, t_arena *arena)
{
	int		y;
	char	**copy;

	y = game->map->last_id + 1;
	while (game->map->array[y][0] == '\0'
		|| is_identifier(game->map->array[y]))
		y++;
	copy = arena_alloc(arena,
			(game->map->char_count * sizeof(char)) + sizeof(char *));
	if (!copy)
		ft_error(5, game);
	while (game->map->array[y][0] == '\n')
		y++;
	copy = copy_loop(game, copy, y);
	return (copy);
}

void	extract_game_map(char *arg, t_game *game, t_arena *arena)
{
	int		fd;

	fd = open(arg, O_RDONLY);
	game->map->height = get_rows(arg, game);
	get_map_array(game, fd, arena);
	close(fd);
	game->final_map = copy_map(game, arena);
	count_symbols(game, 0, 0);
}
