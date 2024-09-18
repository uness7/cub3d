/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:03:49 by yzioual           #+#    #+#             */
/*   Updated: 2024/09/18 10:17:14 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

double	get_player_angle(t_game *game)
{
	if (game->player.orientation == NORTH)
		return (3 * M_PI / 2);
	return (0);
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D", false);
	game->pixel = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void	init_minimap(t_game *game)
{
}

void	init_player(t_game *game)
{
	game->player.x = game->player.x * TILESIZE + TILESIZE / 2;
	game->player.y = game->player.y * TILESIZE + TILESIZE / 2;
	game->player.rd_fov = (FOV * M_PI) / 10;
	game->player.angle = get_player_angle(game);
	game->player.ws = 0;
	game->player.ad = 0;
}

void	init_textures(t_game *game)
{
	game->map->textures.east_tx = mlx_load_png(game->map->textures.east);
	if (!game->map->textures.east_tx)
		error(game, NULL, true, "malloc");
	game->map->textures.north_tx = mlx_load_png(game->map->textures.north);
	if (!game->map->textures.east_tx)
		error(game, NULL, true, "malloc");
	game->map->textures.south_tx = mlx_load_png(game->map->textures.south);
	if (!game->map->textures.east_tx)
		error(game, NULL, true, "malloc");
	game->map->textures.west_tx = mlx_load_png(game->map->textures.west);
	if (!game->map->textures.east_tx)
		error(game, NULL, true, "malloc");
}
