#include "cub3d.h"

bool	check_sep(char current, char *sep)
{
	int	index;

	index = 0;
	while (sep[index] != '\0')
	{
		if (sep[index] == current)
			return (1);
		index++;
	}
	return (0);
}

char	**do_da_malloc(char **arr, char *str, char *sep, t_arena *arena)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = 0;
	while (str[i] != '\0')
	{
		size = 0;
		while (check_sep(str[i], sep) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		while (!check_sep(str[i], sep) && str[i] != '\0')
		{
			i++;
			size++;
		}
		arr[j] = arena_alloc(arena, size + 1);
		j++;
	}
	return (arr);
}

int	count_strs(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (check_sep(str[i], sep) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		count++;
		while (!check_sep(str[i], sep) && str[i] != '\0')
			i++;
	}
	return (count);
}

char	**strs_to_arr(char **dest, char *str, char *sep)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		k = 0;
		while (check_sep(str[i], sep) && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			break ;
		while (!check_sep(str[i], sep) && str[i] != '\0')
		{
			dest[j][k] = str[i];
			i++;
			k++;
		}
		dest[j][k] = '\0';
		j++;
	}
	dest[j] = 0;
	return (dest);
}

char	**arena_setsplit(t_arena *arena, char *str, char *charset)
{
	char	**dest;
	int		count;

	count = count_strs(str, charset);
	dest = arena_alloc (arena, (count + 1) * sizeof(char *));
	do_da_malloc(dest, str, charset, arena);
	strs_to_arr(dest, str, charset);
	return (dest);
}
