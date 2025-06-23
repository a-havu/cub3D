#include "cub3d.h"

static void	get_map_array(t_game *game, int fd)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	game->map->array = ft_calloc(game->map->height + 1, sizeof(char *));//arena_alloc
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
		game->map->array[i] = ft_strdup(line);
		i++;
	}
	game->map->array[i] = NULL;
}

//worry later: Swen & Bug in same room

static void	flood_fill(t_game *game, int y, int x)
{
	game->map_cpy[y][x] = 'A';
	if (game->map_cpy[y][x - 1] != '1' && game->map_cpy[y][x - 1] != ' ' && game->map_cpy[y][x - 1] != 'A')
	{
		if (x == 0)
		{
			// ft_printf("x: %i\n", x);//
			// ft_printf("error: %c\n", game->map_cpy[y][x - 1]);
			ft_error(6, game);
		}
		flood_fill(game, y, (x - 1));
	}
	if (game->map_cpy[y + 1][x] != '1' && game->map_cpy[y + 1][x] != ' ' && game->map_cpy[y + 1][x] != 'A')
	{
		if (y == game->map->height)
		{
			// ft_printf("y: %i, x: %i, height: %i\n", y, x, game->map->height);
			// ft_printf("error: %c\n", game->map_cpy[y + 1][x]);
			ft_error(6, game);
		}
		flood_fill(game, (y + 1), x);
	}
	if (game->map_cpy[y][x + 1] != '1' && game->map_cpy[y][x + 1] != ' ' && game->map_cpy[y][x + 1] != 'A')
	{
		if (x == ft_len(game->map_cpy[y]))
		{
			// ft_printf("x: %i\n", x);
			// ft_printf("error: %c\n", game->map_cpy[y][x + 1]);
			ft_error(6, game);
		}
		flood_fill(game, y, (x + 1));
	}
	if (game->map_cpy[y - 1][x] != '1' && game->map_cpy[y - 1][x] != ' ' && game->map_cpy[y - 1][x] != 'A')
	{
		if (y == 0)
		{
			// ft_printf("y: %i\n", y);
			// ft_printf("error: %c\n", game->map_cpy[y - 1][x]);
			ft_error(6, game);
		}
		flood_fill(game, (y - 1), x);
	}
}

static void	copy_map(t_game *game)
{
	int	y;
	int	i;

	i = 0;
	y = game->map->last_id + 2;
	game->map_cpy = ft_calloc((game->map->height + 1), sizeof(char *));//arena_alloc
	if (!game->map_cpy)
		ft_error(1, game);
	while (game->map->array[y])
	{
		game->map_cpy[i] = ft_strdup(game->map->array[y]);
		if (!game->map_cpy[i])
			ft_error(5, game);
		y++;
		i++;
	}
	game->map_cpy[i] = NULL;
}

void	extract_game_map(char *arg, t_game *game)
{
	int		i;
	int		y;
	int		x;
	int		fd;

	fd = open(arg, O_RDONLY);
	i = 0;
	y = 0;
	game->map->height = get_rows(arg, game);
	get_map_array(game, fd);
	while (ft_strncmp(game->map->array[i],
		game->map->last_identifier, ft_strlen(game->map->last_identifier)))
			i++;
	i++;
	free(game->map->last_identifier);
	copy_map(game);
	//check_spaces();
	while (y <= game->map->height)
	{
		x = 0;
		while (x < ft_len(game->map_cpy[y]))
		{
			//ft_printf("y: %d x: %d game->map_cpy[y][x]: %c\n", y, x, game->map_cpy[y][x]);
			if (game->map_cpy[y][x] != ' ' && game->map_cpy[y][x] != '\0' 
				&& game->map_cpy[y][x] != '1' && game->map_cpy[y][x] != '\n')
			{
				//ft_printf("Sending: %c from y: %i, x: %i\n", game->map_cpy[y][x], y, x);
				flood_fill(game, y, x);
			}
			x++;
		}
		y++;
	}
	count_symbols(game, i);
}
