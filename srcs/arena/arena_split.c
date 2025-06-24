#include "cub3d.h"

static int	word_count(char const *s, char c)
{
	int	i;
	int	w;

	w = 0;
	i = 0;
	if (!*s)
		return (0);
	if (s[0] != c)
		w++;
	while (s[i])
	{
		if ((s[i] == c) && (s[i + 1] != c))
			w++;
		i++;
	}
	if (*s && s[ft_len(s) - 1] == c)
		w--;
	return (w);
}

static void	free_everything(char **str_array)
{
	int	i;

	i = 0;
	while (str_array[i])
	{
		free(str_array[i]);
		str_array[i] = NULL;
		i++;
	}
	free(str_array);
}

static char	*fill_word(char const *s, int *ind, char **str_arr, t_arena *arena)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = arena_alloc(arena, (ind[0] - (ind[1] + 1)) * sizeof(char));
	if (!tmp)
	{
		free_everything(str_arr);
		return (NULL);
	}
	while (ind[1] < ind[0])
	{
		tmp[i] = s[ind[1]];
		ind[1] += 1;
		i++;
	}
	return (tmp);
}

char	**arena_split(t_arena *arena, char const *s, char c)
{
	char	**str_array;
	int		nums[2];
	int		x;

	nums[0] = 0;
	nums[1] = -1;
	x = 0;
	if (!s)
		return (NULL);
	str_array = arena_alloc(arena, (word_count(s, c) + 1) * sizeof(char *));
	if (!str_array)
		return (NULL);
	while (nums[0] <= ft_len(s))
	{
		if (s[nums[0]] != c && nums[1] < 0)
			nums[1] = nums[0];
		else if ((s[nums[0]] == '\0' || s[nums[0]] == c) && nums[1] >= 0)
		{
			str_array[x++] = fill_word(s, nums, str_array, arena);
			nums[1] = -1;
		}
		nums[0] += 1;
	}
	return (str_array);
}
