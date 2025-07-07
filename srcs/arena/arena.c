#include "cub3d.h"
#include <stdio.h>

t_arena	*create_arena(size_t capacity)
{
	void	*data;
	t_arena	*arena;
	size_t	size;
	size_t	data_cap;

	size = round_to_eight(sizeof(t_arena));
	data_cap = round_to_eight(capacity);
	arena = ft_calloc(size, 1);
	if (!arena)
		return (NULL);
	data = ft_calloc(sizeof(uint8_t), data_cap);
	if (!data)
		return (NULL);
	arena->capacity = capacity;
	arena->size = 0;
	arena->data = data;
	arena->next = NULL;
	return (arena);
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	void	*data;
	t_arena	*current;

	size = round_to_eight(size);
	current = arena;
	if (size > current->capacity)
		return (NULL);
	if ((current->size + size) > current->capacity && current->next == NULL)
	{
		current->next = create_arena(current->capacity);
		if (current->next == NULL || current->next->data == NULL)
			return (NULL);
		current = current->next;
	}
	data = &current->data[current->size];
	current->size += size;
	return (data);
}

void	clean_arena(t_arena *arena)
{
	t_arena	*current;
	t_arena	*temp;

	current = arena;
	while (current)
	{
		current->capacity = 0;
		current->size = 0;
		if (current->data)
			free(current->data);
		temp = current->next;
		if (current)
			free(current);
		current = temp;
	}
}

//for testing
void	print_arena_details(t_arena *arena)
{
	int		i;
	t_arena	*current;

	current = arena;
	i = 0;
	while (current)
	{
		ft_printf("Arena Node: %d\n", i + 1);
		ft_printf("Arena Capacity: %zu\n", arena->capacity);
		ft_printf("Arena Size: %zu\n", arena->size);
		ft_printf("Arena data pointer: %p\n", arena->data);
		++i;
		current = current->next;
	}
}
