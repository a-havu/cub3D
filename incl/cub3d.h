#ifndef CUB3D_H
# define CUB3D_H

# include "libft_plus.h"
# include "libftprintf.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

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
	char	**array;
	char	*one_d_array;
	int		height;
	size_t	width;
	t_point	player_pos;
	size_t	player;
	size_t	no;
	size_t	so;
	size_t	we;
	size_t	ea;
	size_t	f;
	size_t	c;
	char	*no_wall;
	char	*so_wall;
	char	*we_wall;
	char	*ea_wall;
	char	*f_value;
	char	*c_value;
	char	*last_identifier;
	int		last_id;
	//player facing direction (N, S, W or E)?
}				t_map;

typedef struct	s_textures
{
	mlx_texture_t	*n_wall;
	mlx_texture_t   *e_wall;
	mlx_texture_t   *s_wall;
	mlx_texture_t   *w_wall;
	mlx_texture_t	*sky;
	mlx_texture_t   *ground;
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

typedef struct	s_game
{
	mlx_t		*mlx;
	t_map		*map;
	char		**map_cpy;
	t_images	*images;
	mlx_image_t	*minimap_base;
	t_textures	*textures;
	//size_t	collected //number of insects found
}				t_game;

void	check_args(int argc, char *arg);
void	check_map(char *arg, t_game *game);
void	clean_up(t_game *game);
void	count_symbols(t_game *game, int i);
void	extract_game_map(char *arg, t_game *game);
void	find_identifiers(char **elements, t_game *game);
void	*free_2d_arr(char **arr);
void	ft_error(int num, t_game *game);
int		ft_len(const char *s);
char    **ft_split_charset(char *str, char *charset);
int		get_rows(char *arg, t_game *game);
mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map);
bool	is_identifier(char *element);
// initialisation
mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map);
void	initialise_images(t_game *game, t_images *images);
void	place_minimap(t_map *map, t_images *images, mlx_t *mlx);

// utilities
void	exit_process(t_map *map);
void	img_error(t_game *game, char signal);
void	delete_textures(t_game *game);

// movement
void	key_input(mlx_key_data_t keydata, void *param);

#endif
