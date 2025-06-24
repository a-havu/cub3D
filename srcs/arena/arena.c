#include "cub3d.h"

int create_arena(t_arena *arena, size_t capacity)
{
    void    *data;

    arena = ft_calloc(sizeof(t_arena), 1);
    if (!arena)
        return(1);
    data = ft_calloc(sizeof(uint8_t), capacity);
    if (!data)
        return (2);
    arena->capacity = capacity;
    arena->size = 0;
    arena->data = data;
    arena->next = NULL;
    return (0);
}

void    *arena_alloc(t_arena *arena, size_t size)
{
    void    *data;
    t_arena *current;
    int     i;

    if (size > current->capacity)
        return (NULL);
    current = arena;
    if ((current->size + size) > current->capacity && current->next == NULL)
    {
        create_arena(current->next, current->capacity);
        if (current->next == NULL || current->next->data == NULL)
            return (NULL);
        current = current->next;
    }
    data = &current->data[current->size];
    current->size += size;
    return (data);
}

void    clean_arena(t_arena *arena)
{
    t_arena *current;
    t_arena *temp;

    current = arena;
    while (current)
    {
        current->capacity = 0;
        current->size_t = 0;
        free(current->data);
        temp = current->next;
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
		ft_printf("Arena Node: %d\n", i + 1);//
		ft_printf("Arena Capacity: %zu\n", arena->capacity);//
		ft_printf("Arena Size: %zu\n", arena->size);//
		ft_printf("Arena data pointer: %p\n", arena->data);//
		++i;
		current = current->next;
	}
}