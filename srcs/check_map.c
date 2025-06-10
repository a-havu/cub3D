#include "../incl/cub3d.h"

static void	convert_cub_to_array(t_map *map, int fd, int rows)
{
	char	*line;
	int		y;

	line = NULL;
	y = 0;
	map->array = ft_calloc(rows + 1, sizeof(char *));
	if (!map->array)
		ft_error(1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '\n'))
			*ft_strchr(line, '\n') = '\0';
		y++;
	}
	map->array[y] = NULL;
}

static void	check_paths(char **elements)
{
	int	i;

	i = 0;
	while(elements[i])
	{
		if (is_identifier(elements[i]))
		{
			i++;
			if (open(elements[i], O_RDONLY) == -1)//vai mika tsekkausfunktio? read?
				ft_error(66);
		}
		i++;
	}
}

static void	check_cub_elements(t_map *map, int fd)
{
	int		i;
	char	**elements;

	i = 0;
	while(map->array[i])
	{
		elements = ft_split_charset(map->array[i], " \n");//tabs? also this doesnt work :D need to append somehow
		i++;
	}
	find_identifiers(elements, map);
	check_paths(elements);
	free_2d_arr(elements);
}

void	check_map(char *arg, t_map *map)
{
	int		fd;
	int		rows;

	rows = get_rows(arg, map);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		ft_error(8);
	convert_cub_to_array(map, fd, rows);
	check_cub_elements(map, fd); // check the NO, SO, WE, EA and the colours
	//copy the map to a separate map array
	close(fd);
}
