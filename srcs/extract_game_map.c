#include "cub3d.h"

void	get_map_array(t_game *game, int fd, t_arena *arena)
{
	char	*line;
	int		i;

	i = 0;
	game->map->array = arena_alloc(arena, (game->map->height + 1 + sizeof(char *)));
	if (!game->map->array)
		ft_error(1, game);
	while (1)
	{
		line = arena_next_line(fd, arena);
		ft_printf("line: %s\n", line);
		if (!line)
			break ;
		// if (ft_strchr(line, '\n'))
		// 	*ft_strchr(line, '\n') = '\0';
		if (ft_strlen(line) > game->map->width)
			game->map->width = ft_strlen(line);
		game->map->array[i] = arena_strdup(arena, line);
		ft_printf("get_map_array: %s", game->map->array[i]);
		i++;
	}
	game->map->array[i] = NULL;
	close(fd);
}

//worry later: Swen & Bug in same room

void	copy_map(t_game *game, t_arena *arena)
{
	int	y;
	int	i;

	i = 0;
	y = game->map->last_id + 1;
	game->map_cpy = arena_alloc(arena, (game->map->char_count * sizeof(char)) + sizeof(char *));
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

static void	do_final_map(t_game *game, t_arena *arena, int i)
{
	int	k;

	k = 0;
	game->final_map = arena_alloc(arena, (game->map->char_count * sizeof(char) + sizeof(char *)));
	while(game->map->array[i])
	{
		if (game->map->array[i][0] != '\n')
		{
			game->final_map[k] = arena_strdup(arena, game->map->array[i]);
			if (!game->final_map[k])
				ft_error(5, game);
		}
		i++;
		k++;
	}
	game->final_map[k] = NULL;
}

void	extract_game_map(char *arg, t_game *game, t_arena *arena)
{
	int		i;
	int		fd;

	fd = open(arg, O_RDONLY);
	i = 0;
	game->map->height = get_rows(arg, game);
	get_map_array(game, fd, arena);
	close(fd);
	while (ft_strncmp(game->map->array[i],
		game->map->last_identifier, ft_strlen(game->map->last_identifier)))
			i++;
	i++;
	do_final_map(game, arena, i);
	count_symbols(game);
}
