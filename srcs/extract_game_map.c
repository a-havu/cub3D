#include "cub3d.h"

static void	get_map_array(t_game *game, int fd, t_arena *arena)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	game->map->array = arena_alloc(arena, game->map->height + 1 * sizeof(char *));
	if (!game->map->array)
		ft_error(1, game);
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
		i++;
	}
	game->map->array[i] = NULL;
}

//worry later: Swen & Bug in same room

static void	copy_map(t_game *game, t_arena *arena)
{
	int	y;
	int	i;

	i = 0;
	y = game->map->last_id + 1;
	game->map_cpy = arena_alloc(arena, (game->map->height + 1) * sizeof(char *));
	if (!game->map_cpy)
		ft_error(1, game);
	while (game->map->array[y])
	{
		game->map_cpy[i] = arena_strdup(arena, game->map->array[y]);
		if (!game->map_cpy[i])
			ft_error(5, game);
		y++;
		i++;
	}
	game->map_cpy[i] = NULL;
	game->map->height = i;
}

void	extract_game_map(char *arg, t_game *game, t_arena *arena)
{
	int		i;
	int		k;
	int		fd;

	fd = open(arg, O_RDONLY);
	i = 0;
	k = 0;
	game->map->height = get_rows(arg, game);
	game->final_map = arena_alloc(arena, (game->map->height + 1) * sizeof(char *));
	get_map_array(game, fd, arena);
	while (ft_strncmp(game->map->array[i],
		game->map->last_identifier, ft_strlen(game->map->last_identifier)))
			i++;
	i += 2;
	copy_map(game, arena);
	while(game->map->array[i])
	{
		game->final_map[k] = arena_strdup(arena, game->map->array[i]);
		if (!game->final_map[k])
			ft_error(5, game);
		i++;
	}
	game->final_map[k] = NULL;
	count_symbols(game);
}
