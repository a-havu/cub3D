#include "../incl/cub3d.h"

void	check_args(int argc, char *arg)
{
	if (argc != 2 || ft_strlen(arg) < 5)
	{
		ft_putstr_fd("\033[91mError\nInvalid argument!☝️\n\033[0m", 2);
		exit(EXIT_FAILURE);
	}
	if (open(arg, O_RDONLY) == -1)
	{
		ft_putstr_fd("\033[91mError\nYour map's not valid💅\n\033[0m", 2);
		exit(EXIT_FAILURE);
	}
}

void	count_symbols(t_game *game)
{
	int	i;

	i = game->map->i;
	while (game->map->one_d_array[i])
	{
		if (game->map->one_d_array[i] == 'N' || game->map->one_d_array[i] == 'S'
				|| game->map->one_d_array[i] == 'E'
				|| game->map->one_d_array[i] == 'W')
			game->map->player++;
		else if (game->map->one_d_array[i] != '0' && game->map->one_d_array[i] != '1' 
			 && game->map->one_d_array[i] != '\n' && game->map->one_d_array[i] != ' ')
				ft_error(4, game);
		i++;
	}
	if (game->map->player > 1)
		ft_error(2, game);
	else if (game->map->player == 0)
		ft_error(3, game);
}
