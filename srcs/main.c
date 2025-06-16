#include "cub3d.h"
#include <stdio.h>

// bool	fits_monitor(mlx_t *mlx)
// {
// 	int32_t	width;
// 	int32_t	height;

// 	mlx_get_monitor_size(0, &width, &height);
// 	if (width < MAX_W || height < MAX_H)
// 	{
// 		ft_printf("error\n");
// 		return (false);
// 	}
// 	return (true);
// }

// void	hook(void *param)
// {
// 	t_game	*game;

// 	game = param;
	
// }

char	*sl_strjoin(char *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	int		total_len;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	total_len = len_s1 + len_s2;
	ft_memcpy((s1 + len_s1), s2, len_s2);
	s1[total_len] = '\0';
	return (s1);
}

int	map_len(t_map *map)
{
	int		total_len;
	char	*line;
	int		fd;

	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		exit_process(map);
	total_len = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(line);
			break ;
		}
		total_len += ft_strlen(line);
		free(line);
	}
	close(fd);
	return (total_len);
}

void	map_to_file(t_map *map)
{
	int	fd;

	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		exit_process(map);
	map->file = ft_calloc(map->len + 1, sizeof(char));
	if (map->file == NULL)
		exit_process(map);
	while (1)
	{
		map->line = get_next_line(fd);
		if (map->line == NULL)
			break ;
		map->height++;
		map->file = sl_strjoin(map->file, map->line);
		free(map->line);
	}
	close(fd);
	if (!(*(map->file)))
	{
		free(map->file);
		exit_process(map);
	}
}

char	**map_to_array(t_map *map) //remove
{
	int i = 0;//
	int j = 0;//
	
	map->len = map_len(map);
	map_to_file(map);
	map->array = ft_split(map->file, '\n');
	if (*(map->array) == NULL)
	{
		free(map->file);
		exit_process(map);
	}
	free(map->file);
	while (map->array[i])
	{
		j = 0;
		while (map->array[i][j])
		{
			if (map->array[i][j] == 'N')
			{
				//ft_printf("i: %i j: %i\n", i, j);
				map->plr_pos.x = j;
				map->plr_pos.y = i;
			}
			j++;
		}
		i++;
	}
	return (map->array);
}

int main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_images	images;
	t_textures	textures;
	t_arena		*arena;

	arena = create_arena(CAPACITY);
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&textures, 0, sizeof(t_textures));
	game.map = &map; // create a set game info function for next 5 lines
	game.images = &images;
	game.textures = &textures;
	map.name = ft_strdup(argv[1]);//
	//parse args
	//error check map
	game.mlx = initialise_mlx(game.mlx, game.map);
	initialise_images(&game, &images);
	map.array = map_to_array(&map); //remove
	//place game image
	place_minimap(&map, &images, game.mlx); //
	mlx_key_hook(game.mlx, &key_input, &game);
	mlx_loop(game.mlx);
	delete_textures(&game);
	mlx_terminate(game.mlx);
	exit_process(&map);
	return (0);
}
