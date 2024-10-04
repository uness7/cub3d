#include "../../inc/cub3d.h"

void	load_colors(t_game *game, char **colors)
{
	int	i;

	i = 0;
	while (colors[i] != NULL)
	{
		if (ft_strncmp(colors[i], "F", 1) == 0)
			get_colors(game, colors[i], "floor");
		else if (ft_strncmp(colors[i], "C", 1) == 0)
			get_colors(game, colors[i], "ceiling");
		else
			ft_putstr_fd("Something went wrong\n", 2);
		i++;
	}
}

void	print_game_data(t_game *game)
{
	ft_putstr_fd("Printing floor colors: \n", 1);
	printf("R value : %d\n", game->map->floor.r);
	printf("G value : %d\n", game->map->floor.g);
	printf("B value : %d\n", game->map->floor.b);
	printf("RGB value : %d\n", game->map->floor.rgb);
	printf("\n");
	ft_putstr_fd("Printing ceiling colors: \n", 1);
	printf("R value : %d\n", game->map->ceiling.r);
	printf("G value : %d\n", game->map->ceiling.g);
	printf("B value : %d\n", game->map->ceiling.b);
	printf("RGB value : %d\n", game->map->ceiling.rgb);
	printf("\n");
	printf("NO Texture %s\n", game->map->textures.north);
	printf("SO Texture %s\n", game->map->textures.south);
	printf("EA Texture %s\n", game->map->textures.east);
	printf("WE Texture %s\n", game->map->textures.west);
	printf("\n");
	if (game->map->map_cpy != NULL)
		ft_put2d_char(game->map->map_cpy);
	printf("\n");
	if (game->player.orientation == NORTH)
		printf("Player's orientation is north\n");
	if (game->player.orientation == SOUTH)
		printf("Player's orientation is south\n");
	if (game->player.orientation == EAST)
		printf("Player's orientation is east\n");
	if (game->player.orientation == WEST)
		printf("Player's orientation is west\n");
	printf("Player's x coordinates: %f\n", game->player.x);
	printf("Player's y coordinates: %f\n", game->player.y);
	printf("Player's angle: %f\n", game->player.angle);
	printf("Player's rd_fov: %f\n", game->player.rd_fov);
	printf("Player's ws: %d\n", game->player.ws);
	printf("Player's as: %d\n", game->player.ad);
}
