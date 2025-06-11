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

void	count_symbols(t_game *game)
{
	int	i;
	int	k;

	i = 0;
	if (!game->map->array[i])
		ft_error(11, game);
	while (game->map->array[i])
	{
		k = 0;
		while (game->map->array[i][k])
		{
			if (game->map->array[i][k] == 'N' || game->map->array[i][k] == 'S'
					|| game->map->array[i][k] == 'E'
					|| game->map->array[i][k] == 'W')
				game->map->player++;
			else if (game->map->array[i][k] != '0'
				&& game->map->array[i][k] != '1')
				ft_error(4,  game);
			k++;
		}
		i++;
	}
	if (game->map->player > 1)
		ft_error(2, game);
	else if (game->map->player == 0)
		ft_error(3, game);
}

