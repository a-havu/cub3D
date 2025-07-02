#include "cub3d.h"

static void	convert_cub_to_one_d_array(t_game *game, int fd, t_arena *arena)
{
	char	*line;

	line = NULL;
	//game->map->one_d_array = NULL;
	game->map->one_d_array = arena_alloc(arena, sizeof(char *));
	if (!game->map->one_d_array)
		ft_error(1, game);
	while (1)
	{
		line = arena_next_line(fd, arena); //tässä kohtaa ei tuu NULLii
		if (!line)
			break ;
		game->map->one_d_array = arena_join(arena, game->map->one_d_array, line);
		if(!game->map->one_d_array)
			ft_error(5, game);
	}
	close(fd);
}

int	cub_atoi(t_game *game, char *str)
{
	int	res;
	
	res = 0;
	while (*str >= 48 && *str <= 57)
	{
		res *= 10;
		res += *str - '0';
		if (res < 0)
			ft_error(7, game);
		str++;
	}
	if (res > 255)
		ft_error(7, game);
	return (res);
}

/** Sets the ceiling and floor colour identifiers into int arrays. */

void	set_cf_colours(t_game *game, char *id, int info)
{
	int		i;
	char	**colours;

	i = 0;
	while (id[i])
	{
		if (id[i] != ',' && (!ft_isdigit(id[i])))
			ft_error(7, game);
		i++;
	}
	colours = arena_setsplit(game->arena, id, ",");
	i = 0;
	while (colours[i])
	{
		if (ft_strlen(colours[i]) > 3)
			ft_error(7, game);
		if (info == 1)
			game->ceiling[i] = cub_atoi(game, colours[i]);
		else
			game->floor[i] = cub_atoi(game, colours[i]);
		i++;
	}
}

/* splitting the created 1D array to extract the elements (texture paths & colour codes)*/

static void	check_cub_elements(t_game *game, t_arena *arena)
{
	char	**elements;

	elements = arena_setsplit(arena, game->map->one_d_array, " \n");
	if (!elements)
		ft_error(5, game);
	find_identifiers(elements, game);
	set_cf_colours(game, game->map->c_value, 1);
	set_cf_colours(game, game->map->f_value, 2);
}

void	check_map(char *arg, t_game *game, t_arena *arena)
{
	int		fd;

	fd = open(arg, O_RDONLY);
	if (fd == -1)
		ft_error(8, game);
	game->map->height = get_rows(arg, game);
	convert_cub_to_one_d_array(game, fd, arena);
	check_cub_elements(game, arena);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		ft_error(8, game);
	get_map_array(game, fd, arena);
	game->map_cpy = copy_map(game, arena);
	execute_flood_fill(game);
	extract_game_map(arg, game, arena);
	// int i = 0;
	// while (game->final_map[i])
	// {
	// 	ft_printf("final map: %s", game->final_map[i]);
	// 	i++;
	// }
	// ft_printf("path to NO: %s\n", game->map->no_wall);
	// ft_printf("path to SO: %s\n", game->map->so_wall);
	// ft_printf("path to WE: %s\n", game->map->we_wall);
	// ft_printf("path to EA: %s\n", game->map->ea_wall);
	// ft_printf("F value: %s\n", game->map->f_value);
	// ft_printf("C value: %s\n", game->map->c_value);
}
