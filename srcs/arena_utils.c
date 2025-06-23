#include "cub3d.h"

char	*arena_join(t_arena *arena, char const *s1, char const *s2)
{
	char	*new_str;
	size_t	total_len;
	int		i;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	k = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	new_str = arena_alloc(arena, (total_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[k])
		new_str[i++] = s2[k++];
	new_str[i] = '\0';
	return (new_str);
}

char	*arena_strdup(t_arena *arena, const char *s)
{
	int		i;
	char	*new;

	i = 0;
	new = arena_alloc(arena, (ft_strlen(s) + 1) * (sizeof(char)));
	if (!new)
		return (NULL);
	while (s[i])
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
