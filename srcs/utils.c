#include "cub3d.h"

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
		line = arena_next_line(fd, game->arena);
		if (!line)
			break ;
		rows++;
	}
	close(fd);
	return (rows);
}

int	ft_len(const char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		i++;
	}
	return (i);
}

static void	flood_fill(t_game *game, int y, int x)
{
	game->map_cpy[y][x] = 'A';
	if (y <= 0)
		ft_error(6, game);
	if (y >= game->map->height - 1)
		ft_error(6, game);
	if (game->map_cpy[y][x - 1] != '1' && game->map_cpy[y][x - 1] != ' ' && game->map_cpy[y][x - 1] != 'A')
	{
		if (x - 1 <= 0)
			ft_error(6, game);
		flood_fill(game, y, (x - 1));
	}
	if (game->map_cpy[y + 1][x] != '1' && game->map_cpy[y + 1][x] != ' ' && game->map_cpy[y + 1][x] != 'A')
		flood_fill(game, (y + 1), x);
	if (game->map_cpy[y][x + 1] != '1' && game->map_cpy[y][x + 1] != ' ' && game->map_cpy[y][x + 1] != 'A')
	{
		if (x + 1 >= ft_len(game->map_cpy[y]))
			ft_error(6, game);
		flood_fill(game, y, (x + 1));
	}
	if (game->map_cpy[y - 1][x] != '1' && game->map_cpy[y - 1][x] != ' ' && game->map_cpy[y - 1][x] != 'A')
		flood_fill(game, (y - 1), x);
}

void	execute_flood_fill(t_game *game)
{
	int	y;
	int	x;

	y = 1;
	while (y < game->map->height)
	{
		x = 0;
		while (x < ft_len(game->map_cpy[y]))
		{
			if (game->map_cpy[y][x] != ' ' && game->map_cpy[y][x] != '\0' 
				&& game->map_cpy[y][x] != '1')
					flood_fill(game, y, x);
			x++;
		}
		y++;
	}
}
