#include "../incl/cub3d.h"

void	ft_error(int num)
{
	if (num == 1)
		ft_putstr_fd("\033[91mError\nOh no! Initializing failed😤😤🥺\n\033[0m", 2); // tai jotain
	else if (num == 2)
		ft_putstr_fd("\033[91mError\nExtra players! It's not a co-op\n\033[0m", 2);
	else if (num == 3)
		ft_putstr_fd("\033[91mError\nCan't play with no players😔\n\033[0m", 2);
	else if (num == 4)
		ft_putstr_fd("\033[91mError\nUnknown character found!!!👽\n\033[0m", 2);
	// clean up function
	exit(EXIT_FAILURE);
}
