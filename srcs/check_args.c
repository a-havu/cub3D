#include "../incl/cub3d.h"

void	check_args(int argc, char *arg)
{
	if (argc != 2 || ft_strlen(arg) < 5)
	{
		ft_putstr_fd("\033[91mError\nInvalid argument!☝️\n\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(arg) >= 5)
	{
		arg = arg + ft_strlen(arg) - 4;
		if (ft_strncmp(arg, ".cub", 4))
		{
			ft_putstr_fd("\033[91mError\nMap needs to be .cub 🙄\n\033[0m", 2);
			exit(EXIT_FAILURE);
		}
	}
}

void	count_symbols(t_map *map)
{
	int	i;
	int	k;

	i = 0;
	if (!map->array[i])
		ft_error(11);
	while (map->array[i])
	{
		k = 0;
		while (map->array[i][k])
		{
			if (map->array[i][k] == 'N' || map->array[i][k] == 'S'
					|| map->array[i][k] == 'E' || map->array[i][k] == 'W')
				map->player++;
			else if (map->array[i][k] != '0' && map->array[i][k] != '1')
				ft_error(4);
			k++;
		}
		i++;
	}
	if (map->player > 1)
		ft_error(2);
	else if (map->player == 0)
		ft_error(3);
}

