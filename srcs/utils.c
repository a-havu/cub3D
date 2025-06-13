#include "cub3d.h"

void	exit_process(t_map *map)
{
	if (map->array != NULL)
		free_2d_arr(map->array);
	//whatever needs to be freed
	//can also send a msg to this function to print what went wrong?
	exit(1); //or send a code and exit with exit(code);
}

void	*free_2d_arr(char **arr)
{
	size_t	i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (NULL);
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
		line = get_next_line(fd);
		if (!line)
			break ;
		rows++;
		free(line);
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
		line = get_next_line(fd);
		if (!line)
			break ;
		rows++;
		free(line);
	}
	close(fd);
	return (rows);
}
