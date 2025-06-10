#include "../incl/cub3d.h"

int main(int argc, char **argv)
{
	t_game		game;
	t_map		map;
	t_images	images;
	t_textures	textures;

	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	ft_memset(&textures, 0, sizeof(t_textures));
	game.map = &map;
	game.images = &images;
	game.textures = &textures;
	check_args(argc, argv);
	check_map(argv[1], &map);
	game.mlx = initialise_mlx(game.mlx, game.map);

}
