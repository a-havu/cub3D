#include "cub3d.h"

void	load_space_textures(t_game *game)
{
	game->textures->n_wall = mlx_load_png("./textures/n_wall.png");
	if (!game->textures->n_wall)
		img_error(game, 't');
	game->textures->s_wall = mlx_load_png("./textures/s_wall.png");
	if (!game->textures->s_wall)
		img_error(game, 't');
	game->textures->e_wall = mlx_load_png("./textures/e_wall.png");
	if (!game->textures->e_wall)
		img_error(game, 't');
	game->textures->w_wall = mlx_load_png("./textures/w_wall.png");
	if (!game->textures->w_wall)
		img_error(game, 't');
	game->textures->miniwall = mlx_load_png("./textures/miniwall.png");
	if (!game->textures->miniwall)
		img_error(game, 't');
	game->textures->empty = mlx_load_png("./textures/empty.png");
	if (!game->textures->empty)
		img_error(game, 't');
	game->textures->offedge = mlx_load_png("./textures/offedge.png");
	if (!game->textures->offedge)
		img_error(game, 't');
}

void	load_item_textures(t_game *game)
{
	game->textures->door = mlx_load_png("./textures/door.png");
	if (!game->textures->door)
		img_error(game, 't');
	game->textures->camera = mlx_load_png("./textures/camera.png");
	if (!game->textures->camera)
		img_error(game, 't');
	game->textures->insect1 = mlx_load_png("./textures/insect1.png");
	if (!game->textures->insect1)
		img_error(game, 't');
	game->textures->insect2 = mlx_load_png("./textures/insect2.png");
	if (!game->textures->insect2)
		img_error(game, 't');
	game->textures->insect3 = mlx_load_png("./textures/insect3.png");
	if (!game->textures->insect3)
		img_error(game, 't');
	game->textures->insect4 = mlx_load_png("./textures/insect4.png");
	if (!game->textures->insect4)
		img_error(game, 't');
}

void	initialise_space(t_game *game, t_images *images)
{
	images->n_wall = mlx_texture_to_image(game->mlx, game->textures->n_wall);
	if (!images->n_wall)
		img_error(game, 'i');
	images->s_wall = mlx_texture_to_image(game->mlx, game->textures->s_wall);
	if (!images->s_wall)
		img_error(game, 'i');
	images->e_wall = mlx_texture_to_image(game->mlx, game->textures->e_wall);
	if (!images->e_wall)
		img_error(game, 'i');
	images->w_wall = mlx_texture_to_image(game->mlx, game->textures->w_wall);
	if (!images->w_wall)
		img_error(game, 'i');
	images->miniwall = mlx_texture_to_image(game->mlx, game->textures->miniwall);
	if (!images->miniwall)
		img_error(game, 'i');
	images->empty = mlx_texture_to_image(game->mlx, game->textures->empty);
	if (!images->empty)
		img_error(game, 'i');
	images->offedge = mlx_texture_to_image(game->mlx, game->textures->offedge);
	if (!images->offedge)
		img_error(game, 'i');
}

void	initialise_items(t_game *game, t_images *images)
{
	images->door = mlx_texture_to_image(game->mlx, game->textures->door);
	if (!images->door)
		img_error(game, 'i');
	images->camera = mlx_texture_to_image(game->mlx, game->textures->camera);
	if (!images->camera)
		img_error(game, 'i');
	images->insect1 = mlx_texture_to_image(game->mlx, game->textures->insect1);
	if (!images->insect1)
		img_error(game, 'i');
	images->insect2 = mlx_texture_to_image(game->mlx, game->textures->insect2);
	if (!images->insect2)
		img_error(game, 'i');
	images->insect3 = mlx_texture_to_image(game->mlx, game->textures->insect3);
	if (!images->insect3)
		img_error(game, 'i');
	images->insect4 = mlx_texture_to_image(game->mlx, game->textures->insect4);
	if (!images->insect4)
		img_error(game, 'i');
}

void	initialise_images(t_game *game, t_images *images)
{
	load_space_textures(game);
	load_item_textures(game);
	initialise_space(game, images);
	initialise_items(game, images);
}

mlx_t	*initialise_mlx(mlx_t *mlx, t_map *map)
{
	mlx = mlx_init(MAX_W, MAX_H, "cub3D", true);
	if (!mlx)
		exit_process(map); //error msg "MLX initialisation failed\n"
	return (mlx);
}
