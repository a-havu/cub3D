#ifndef CUB3D_H
# define CUB3D_H

# include "libft_plus.h"
# include "libftprintf.h"
# include <math.h>
# include <fcntl.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h> //remove

# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53
# define PXL 64 //tai kuinka iso se oliska
# define MAX_H 2160 // full screen
# define MAX_W 3840 // full screen
# define CAPACITY 1250000 // 10 mb

typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_map
{
	char	*name;
	char	*line;
	char	*file;
	char	**array;
	size_t		height;
	int		width;
	t_point	plr_pos;
	t_point	dir;
	t_point	plane;
	int		len;
	//player facing direction (N, S, W or E)?
}				t_map;

typedef struct	s_textures
{
	mlx_texture_t	*n_wall;
	mlx_texture_t   *e_wall;
	mlx_texture_t   *s_wall;
	mlx_texture_t   *w_wall;
	mlx_texture_t   *miniwall;
	mlx_texture_t   *empty;
	mlx_texture_t   *offedge;
	mlx_texture_t   *door;
	mlx_texture_t   *camera;
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
	mlx_image_t *miniwall;
	mlx_image_t *empty;
	mlx_image_t *offedge;
	mlx_image_t *door;
	mlx_image_t *camera;
	mlx_image_t *insect1;
	mlx_image_t *insect2;
	mlx_image_t *insect3;
	mlx_image_t *insect4;
}				t_images;

typedef struct	s_arena
{
	size_t			capacity;
    size_t			size;
    uint8_t			*data;
    struct s_arena	*next;
}				t_arena;


typedef struct	s_game
{
	mlx_t		*mlx;
	t_map		*map;
	t_images	*images;
	mlx_image_t	*minimap_base;
	t_textures	*textures;
	//size_t	collected //number of insects found
}				t_game;

// initialisation
int create_arena(t_arena *arena, size_t capacity);
mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map);
void	initialise_images(t_game *game, t_images *images);
void	place_minimap(t_map *map, t_images *images, mlx_t *mlx);

// utilities
void	exit_process(t_map *map);
void	img_error(t_game *game, char signal);
void	delete_textures(t_game *game);
char	*arena_join(t_arena *arena, const *s1, char const *s2);
char	*arena_strdup(const char *s);
char	**arena_setsplit(t_arena *arena, char *str, char *charset);

// movement
void	key_input(mlx_key_data_t keydata, void *param);

#endif
