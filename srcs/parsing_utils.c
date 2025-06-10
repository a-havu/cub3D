#include "../incl/cub3d.h"

void	find_identifiers(char **elements, t_map *map)
{
	int	i;

	i = 0;
	while(elements[i])
	{
		if (!ft_strncmp(elements[i], "NO", 3))
			map->no++;
		else if (!ft_strncmp(elements[i], "SO", 3))
			map->so++;
		else if (!ft_strncmp(elements[i], "WE", 3))
			map->we++;
		else if (!ft_strncmp(elements[i], "EA", 3))
			map->ea++;
		else if (!ft_strncmp(elements[i], "F", 3))
			map->f++;
		else if (!ft_strncmp(elements[i], "C", 3))
			map->c++;
		i++;
	}
	if (map->no > 1 || map->so > 1 || map->we > 1 || map->ea > 1)
		ft_error(66);
	if (map->no == 0 || map->so == 0 || map->we == 0 || map->ea == 0)
		ft_error(66);
	// if there are invalid extra identifiers, ft_error
}

bool	is_identifier(char *element)
{
	if (!ft_strncmp(element, "NO", 3))
		return (true);
	else if (!ft_strncmp(element, "SO", 3))
		return (true);
	else if (!ft_strncmp(element, "WE", 3))
		return (true);
	else if (!ft_strncmp(element, "EA", 3))
		return (true);
	else if (!ft_strncmp(element, "F", 3))
		return (true);
	else if (!ft_strncmp(element, "C", 3))
		return (true);
	return (false);
}
