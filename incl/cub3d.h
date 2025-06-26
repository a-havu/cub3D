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
# define CAPACITY 1250000 // 10 mb

typedef struct	s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct	s_map
{
	char	player;
	char	**array;
	char	*one_d_array;
	int		height;
	int		char_count;
	size_t	width;
	t_point	player_pos;
	size_t	player_count;
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

typedef struct	s_arena
{
	size_t			capacity;
    size_t			size;
    uint8_t			*data;
    struct s_arena	*next;
}				t_arena;


typedef struct	s_game
{
	mlx_t			*mlx;
	t_map			*map;
	char			**map_cpy;
	char			**final_map;
	t_images		*images;
	mlx_image_t		*minimap_base;
	t_textures		*textures;
	struct s_arena	*arena;
	//size_t	collected //number of insects found
}				t_game;

//parsing
void	check_args(int argc, char *arg, t_game *game);
void	check_map(char *arg, t_game *game, t_arena *arena);
char	**copy_map(t_game *game, t_arena *arena);
void	count_symbols(t_game *game);
void	execute_flood_fill(t_game *game);
void	extract_game_map(char *arg, t_game *game, t_arena *arena);
void	find_identifiers(char **elements, t_game *game);
void	*free_2d_arr(char **arr);
void	ft_error(int num, t_game *game);
int		ft_len(const char *s);
void	get_map_array(t_game *game, int fd, t_arena *arena);
int		get_rows(char *arg, t_game *game);
mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map);
bool	is_identifier(char *element);

// initialisation
t_arena *create_arena(size_t capacity);
mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map);
void	initialise_images(t_game *game, t_images *images);
void	place_minimap(t_map *map, t_images *images, mlx_t *mlx);

// utilities
void	img_error(t_game *game, char signal);
void	delete_textures(t_game *game);
void    *arena_alloc(t_arena *arena, size_t size);
char	*arena_join(t_arena *arena, char const *s1, char const *s2);
char	*arena_next_line(int fd, t_arena *arena);
char	*arena_strdup(t_arena *arena, const char *s);
char	**arena_setsplit(t_arena *arena, char *str, char *charset);
void    clean_arena(t_arena *arena);
size_t	round_to_eight(size_t num);

// movement
void	key_input(mlx_key_data_t keydata, void *param);

#endif
