#include "cub3d.h"

// void	place_minimap(t_map *map, t_images *images, mlx_t *mlx)
// {
// 	size_t	x;
// 	size_t	y;

// 	y = 0;
// 	while (y < 17) //percentage of width
// 	{
//  		x = 0;
// 		while (x < 24) //percentage of height
// 		{
// 			//mlx_image_to_window(mlx, images->door, x * PXL, y * PXL);
// 			if (map->array[y][x])
// 			{
// 				if (map->array[y][x] == '1')
// 			 		mlx_image_to_window(mlx, images->miniwall, x * 32, y * 32);
// 				else if (map->array[y][x] == '0' || map->array[y][x] == 'P' ||
// 					map->array[y][x] == 'C')
// 					mlx_image_to_window(mlx, images->empty, x * 32, y * 32);
// 				else
// 					mlx_image_to_window(mlx, images->offedge, x * 32, y * 32);
// 			}
// 			else
// 					mlx_image_to_window(mlx, images->offedge, x * 32, y * 32);	
// 			x++;
// 		}
// 		y++;
// 	}
// }

int	ft_pituus(const char *s)
{
	int	counter;

	counter = 0;
	while (*s != '\0')
	{
		s++;
		counter++;
	}
	return (counter);
}

void	place_minimap(t_map *map, t_images *images, mlx_t *mlx)
{
	int	x;
	int	y;
	int	start_x;
	int	start_y;
	int	final_x;

	//ft_printf("x: %i y: %i\n", map->plr_pos.x, map->plr_pos.y);//
	start_x = map->plr_pos.x - 11;
	if (start_x < 0)
		start_x = 0;
	start_y = map->plr_pos.y - 7;
	if (start_y < 0)
		start_y = 0;
	final_x = start_x;
	y = 0;
	while (y < 15) //percentage of width
	{
		x = 0;
		start_x = final_x;
		//ft_printf("x: %i y: %i\n", start_y, start_x);//
		while (x < 23) //percentage of height
		{
			if (start_y < map->height && start_x < ft_pituus(map->array[start_y]))
			{
				if (map->array[start_y][start_x] == '1')
					mlx_image_to_window(mlx, images->miniwall, x * 32, y * 32);
				else if (map->array[start_y][start_x] == '0')
					mlx_image_to_window(mlx, images->empty, x * 32, y * 32);
				else if (map->array[start_y][start_x] == 'N')
				{
					mlx_image_to_window(mlx, images->empty, x * 32, y * 32);
					mlx_image_to_window(mlx, images->door, (x * 32 + 8), (y * 32 + 8));
				}
				else
					mlx_image_to_window(mlx, images->offedge, x * 32, y * 32);
			}
			else
				mlx_image_to_window(mlx, images->camera, x * 32, y * 32);
			x++;
			start_x++;
		}
		y++;
		start_y++;
	}
}

// void	place_minimap(t_map *map, t_images *images, mlx_t *mlx)
// {
// 	size_t	x;
// 	size_t	y;
// 	size_t	start_x;
// 	size_t	start_y;
// 	size_t	final_x;

// 	(void)images;
// 	(void)mlx;
// 	start_x = map->plr_pos.x - 10;
// 	if (start_x < 0)
// 		start_x = 0;
// 	start_y = map->plr_pos.y - 6;
// 	if (start_y < 0)
// 		start_y = 0;
// 	final_x = start_x;
// 	y = 0;
// 	while (y < 14) //percentage of width
// 	{
// 		x = 0;
// 		start_x = final_x;
// 		while (x < 24) //percentage of height
// 		{
// 			if (map->array[start_y][start_x])
// 			{
// 				if (map->array[start_y][start_x] == '1')
// 					ft_printf("1");
// 				else if (map->array[start_y][start_x] == '0' || map->array[start_y][start_x] == 'P' ||
// 					map->array[start_y][start_x] == 'C')
// 					ft_printf("0");
// 				else if (map->array[start_y][start_x] == 'N')
// 					ft_printf("N");
// 				else if (map->array[start_y][start_x] == ' ')
// 					ft_printf("S");
// 				else
// 					ft_printf("%c", map->array[start_y][start_x]);
// 			}
// 			else
// 				ft_printf("X");
// 			x++;
// 			start_x++;
// 		}
// 		y++;
// 		start_y++;
// 		ft_printf("\n");
// 	}
// }