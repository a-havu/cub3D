#include "../incl/cub3d.h"

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
