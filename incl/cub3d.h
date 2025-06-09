#ifndef CUB3D_H
# define CUB3D_H

# include "libft_plus.h"
# include "libftprintf.h"
# include <math.h>

# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define PXL 64 //tai kuinka iso se oliska
# define MAX_H 2160 // full screen
# define MAX_W 3840 // full screen

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct	s_map
{
	char	*name;
	char	*file;
	char	**array;
	size_t	height;
	size_t	width;
	t_point	player_pos;
	//player facing direction (N, S, W or E)?
}				t_map;

typedef struct	s_textures
{
	mlx_texture_t	*n_wall;
	mlx_texture_t   *e_wall;
	mlx_texture_t   *s_wall;
	mlx_texture_t   *w_wall;
	mlx_texture_t	*floor;
	mlx_texture_t   *ground;
	mlx_texture_t   *door;
	mlx_texture_t   *insect1;
	mlx_texture_t   *insect2;
	mlx_texture_t   *insect3;
	mlx_texture_t   *insect4;
}				t_textures;

typedef struct	s_images
{
	mlx_image_t	*n_wall;
	mlx_image_t *e_wall;
	mlx_image_t *s_wall;
	mlx_image_t *w_wall;
	mlx_image_t *floor;
	mlx_image_t *ground;
	mlx_image_t *door;
	mlx_image_t *insect1;
	mlx_image_t *insect2;
	mlx_image_t *insect3;
	mlx_image_t *insect4;
}				t_images;

typedef struct	s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_images	*images;
	t_textures	*textures;
	//size_t	collected //number of insects found
}				t_game;

mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map);

#endif
