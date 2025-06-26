#include "cub3d.h"

void	exit_process(t_map *map)
{
	(void)map;//
	//if (map->array != NULL)
	//	free_arr(map->array);
	//whatever needs to be freed
	//can also send a msg to this function to print what went wrong?
	exit(1); //or send a code and exit with exit(code);
}

void	img_error(t_game *game, char signal)
{
	delete_textures(game);
	mlx_terminate(game->mlx);
	if (signal == 't')
		exit_process(game->map);
	else if (signal == 'i')
		exit_process(game->map);
}

void	delete_textures(t_game *game)
{
	if (game->textures->n_wall)
		mlx_delete_texture(game->textures->n_wall);
	if (game->textures->e_wall)
		mlx_delete_texture(game->textures->e_wall);
	if (game->textures->s_wall)
		mlx_delete_texture(game->textures->s_wall);
	if (game->textures->w_wall)
		mlx_delete_texture(game->textures->w_wall);
	if (game->textures->door)
		mlx_delete_texture(game->textures->door);
	if (game->textures->camera)
		mlx_delete_texture(game->textures->camera);
	if (game->textures->insect1)
		mlx_delete_texture(game->textures->insect1);
	if (game->textures->insect2)
		mlx_delete_texture(game->textures->insect2);
	if (game->textures->insect3)
		mlx_delete_texture(game->textures->insect3);
	if (game->textures->insect4)
		mlx_delete_texture(game->textures->insect4);
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
		line = arena_next_line(fd, game->arena);
		if (!line)
			break ;
		game->map->char_count += ft_strlen(line);
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

{
	game->map_cpy[y][x] = 'A';
	if (y <= 0)
		ft_error(6, game);
	if (y >= game->map->height - 1)
		ft_error(6, game);
	if (game->map_cpy[y][x - 1] != '1' && game->map_cpy[y][x - 1] != ' ' && game->map_cpy[y][x - 1] != 'A')
	{
		if (x - 1 < 0)
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

	y = 0;
	while (y <= game->map->height)
	{
		x = 0;
		while (x < ft_len(game->map_cpy[y]))
		{
			if (game->map_cpy[y][x] != ' ' && game->map_cpy[y][x] != '\0' 
				&& game->map_cpy[y][x] != '1' && game->map_cpy[y][x] != '\n')
					flood_fill(game, y, x);
			x++;
		}
		y++;
	}
}
