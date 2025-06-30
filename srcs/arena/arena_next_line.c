#include "cub3d.h"

static void	clean_stash(char *stash)
{
	char	*tmp_stash;
	size_t	i;

	i = 0;
	tmp_stash = ft_strchr(stash, '\n');
	if (tmp_stash)
	{
		tmp_stash++;
		while (tmp_stash[i])
		{
			stash[i] = tmp_stash[i];
			i++;
		}
	}
	while (stash[i])
		stash[i++] = '\0';
}

static char	*join(char *next_line, char stash[BUFFER_SIZE + 1], t_arena *arena)
{
	char	*tmp;

	tmp = arena_join(arena, next_line, stash);
	if (!tmp)
		return (NULL);
	return (tmp);
}

static char	*fill_line(int fd, char *next_line, char stash[BUFFER_SIZE + 1], t_arena *arena)
{
	int			bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		clean_stash(stash);
		bytes_read = read(fd, stash, BUFFER_SIZE);
		if (bytes_read <= 0 && !next_line[0])
			return (NULL);
		if (bytes_read > 0)
			next_line = join(next_line, stash, arena);
		if (ft_strchr(next_line, '\n'))
			break ;
	}
	clean_stash(stash);
	return (next_line);
}

static char	*clean_next_line(char *next_line)
{
	int	i;

	i = 0;
	if (!next_line)
		return (NULL);
	while (next_line[i] && next_line[i] != '\n')
		i++;
	if (next_line[i] == '\n')
	{	
		i++;
		while (next_line[i])
			next_line[i++] = '\0';
	}
	return (next_line);
}

char	*arena_next_line(int fd, t_arena *arena)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line = arena_alloc(arena, sizeof(char *));
	if (!next_line)
		return (NULL);
	if (stash[0])
	{
		next_line = join(next_line, stash, arena);
		if (ft_strchr(next_line, '\n'))
		{
			clean_stash(stash);
			next_line = clean_next_line(next_line);
			return (next_line);
		}
	}
	next_line = fill_line(fd, next_line, stash, arena);
	next_line = clean_next_line(next_line);
	return (next_line);
}
