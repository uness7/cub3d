/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:36:26 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/10 12:36:26 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_colors(t_game *game, char *rgb, char *space)
{
	t_color	colors;
	char	**split;

	if (rgb == NULL)
	{
		ft_putstr_fd("Error: RGB array in get_colors is NULL\n", 2);
		exit(EXIT_FAILURE);
	}
	split = ft_split(rgb, ',');
	if (!split || !split[0] || !split[1] || !split[2] || !split[3])
	{
		ft_free_2d_char(split);
		ft_putstr_fd("Error: something wrong ft_split function\n", 2);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	colors.r = ft_atoi(split[1]);
	colors.g = ft_atoi(split[2]);
	colors.b = ft_atoi(split[3]);
	colors.rgb = ((colors.r << 24) | (colors.g << 16) | \
			(colors.b << 8) | (0xFF));
	ft_free_2d_char(split);
	init_colors(game, colors, space);
}

void	init_colors(t_game *game, t_color colors, char *space)
{
	if (ft_strncmp(space, "floor", 6) == 0)
		game->map->floor = colors;
	else if (ft_strncmp(space, "ceiling", 8) == 0)
		game->map->ceiling = colors;
	else
	{
		ft_putstr_fd("Error: expected floor or ceiling !\n", 2);
		exit(EXIT_FAILURE);
	}
}

static bool	is_null(mlx_texture_t *texture)
{
	if (texture == NULL)
		return (false);
	return (true);
}

void	load_textures(t_game *game)
{
	if (game->map->textures.north != NULL)
		game->map->textures.north_tx = mlx_load_png(game->map->textures.north);
	if (game->map->textures.south != NULL)
		game->map->textures.south_tx = mlx_load_png(game->map->textures.south);
	if (game->map->textures.east != NULL)
		game->map->textures.east_tx = mlx_load_png(game->map->textures.east);
	if (game->map->textures.west != NULL)
		game->map->textures.west_tx = mlx_load_png(game->map->textures.west);
	if (!is_null(game->map->textures.north_tx) || \
			!is_null(game->map->textures.south_tx) || \
			!is_null(game->map->textures.east_tx) || \
			!is_null(game->map->textures.west_tx))
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		return ;
	}
}

int	load_map(t_game *game, char **map, int num_lines)
{
	int	i;

	i = -1;
	while (++i < num_lines)
	{
		game->map->map_cpy[i] = ft_strdup(map[i]);
		if (game->map->map_cpy[i] == NULL)
			return (-1);
	}
	game->map->map_cpy[i] = NULL;
	return (0);
}
