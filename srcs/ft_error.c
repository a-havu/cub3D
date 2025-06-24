#include "cub3d.h"

void	ft_error(int num, t_game *game)
{
	if (num == 1)
		ft_putstr_fd("\033[91mError\nInitialising failed😤😤🥺\n\033[0m", 2);
	else if (num == 2)
		ft_putstr_fd("\033[91mError\nExtra players! It's not a co-op\n\033[0m", 2);
	else if (num == 3)
		ft_putstr_fd("\033[91mError\nCan't play with no players😔\n\033[0m", 2);
	else if (num == 4)
		ft_putstr_fd("\033[91mError\nUnknown character found!!!👽\n\033[0m", 2);
	else if (num == 5)
		ft_putstr_fd("\033[91mError\nMemory allocation failure💀💀\n\033[0m", 2);
	else if (num == 6)
		ft_putstr_fd("\033[91mError\nYour map's not valid💅\n\033[0m", 2);
	else if (num == 7)
		ft_putstr_fd("\033[91mError\nInvalid identifiers🧭\n\033[0m", 2);
	clean_arena(game->arena);
	exit(EXIT_FAILURE);
}
