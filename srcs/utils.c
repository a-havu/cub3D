void	exit_process(t_map *map)
{
	if (map->array != NULL)
		free_arr(map->array);
	//whatever needs to be freed
	//can also send a msg to this function to print what went wrong?
	exit(1); //or send a code and exit with exit(code);
}
