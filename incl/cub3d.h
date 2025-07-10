/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 12:16:15 by ahavu             #+#    #+#             */
/*   Updated: 2025/07/10 12:16:18 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft_plus.h"
# include "libftprintf.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>

# define MAX_H 2160
# define MAX_W 3840
# define CAPACITY 1250000
# define ROT 0.02
# define TILE_SIZE 30

# define UP -1
# define LEFT -1
# define DOWN 1
# define RIGHT 1

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_spot
{
	int	x;
	int	y;
}				t_spot;

typedef struct s_map
{
	char	player;
	char	**array;
	char	*one_d_array;
	int		height;
	int		char_count;
	size_t	width;
	t_point	plr_pos;
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
}				t_map;

typedef struct s_textures
{
	mlx_texture_t	*n_wall;
	mlx_texture_t	*e_wall;
	mlx_texture_t	*s_wall;
	mlx_texture_t	*w_wall;
}				t_textures;

typedef struct s_arena
{
	size_t			capacity;
	size_t			size;
	uint8_t			*data;
	struct s_arena	*next;
}				t_arena;

typedef struct s_minimap
{
	int			tile_size;
	mlx_image_t	*map;
	mlx_image_t	*player;
	uint32_t	colour;
	float		scale_fctr;
}				t_minimap;

typedef struct s_game
{
	mlx_t				*mlx;
	t_map				*map;
	char				**map_cpy;
	char				**final_map;
	mlx_image_t			*screen;
	t_textures			*textures;
	t_point				dir;
	t_point				raydir;
	t_point				plane;
	t_point				side_dist;
	t_point				delta;
	t_spot				sqr;
	t_spot				step;
	t_spot				tex;
	int					ceiling[3];
	int					floor[3];
	int					side;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					tex_num;
	int					tex_w;
	int					tex_h;
	bool				hit;
	double				wall_dist;
	double				camera_x;
	double				wall_x;
	double				incr;
	double				tex_pos;
	struct s_arena		*arena;
	struct s_minimap	*minimap;
}				t_game;

//parsing
void		check_args(int argc, char *arg, t_game *game);
void		check_map(char *arg, t_game *game, t_arena *arena);
char		**copy_map(t_game *game, t_arena *arena);
void		count_symbols(t_game *game, int y, int x);
void		execute_flood_fill(t_game *game);
void		extract_game_map(char *arg, t_game *game, t_arena *arena);
void		find_identifiers(char **elements, t_game *game);
void		ft_error(int num, t_game *game);
void		ft_error_graphics(t_game *game);
int			ft_len(const char *s);
void		get_map_array(t_game *game, int fd, t_arena *arena);
int			get_rows(char *arg, t_game *game);
bool		is_identifier(char *element);

// initialisation
t_arena		*create_arena(size_t capacity);
void		draw_minimap_loop(t_game *game, int y, int x);
void		init_minimap_values(t_game *game);
void		init_player(t_game *game);
mlx_t		*initialise_mlx(t_game *game);
void		initialise_images(t_game *game);
void		place_minimap(t_game *game);
void		init_struct(t_game *game);

// utilities
void		delete_textures(t_textures *textures);
void		*arena_alloc(t_arena *arena, size_t size);
char		*arena_join(t_arena *arena, char const *s1, char const *s2);
char		*arena_next_line(int fd, t_arena *arena);
char		*arena_strdup(t_arena *arena, const char *s);
char		**arena_setsplit(t_arena *arena, char *str, char *charset);
void		clean_arena(t_arena *arena);
size_t		round_to_eight(size_t num);

// movement
void		draw_player(t_game *game);
void		update_view(void *param);

// graphics
uint32_t	get_colour(int r, int g, int b);
void		raycasting(t_game *game);
void		draw(t_game *game, int x);
void		draw_cf(mlx_image_t *screen, t_game *game);
void		rotate(t_game *game, double rot);

#endif
