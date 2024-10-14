/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:39:37 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/12 11:43:05 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game	*allocate_memory_for_game(void)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (game == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		return (NULL);
	}
	ft_memset(game, 0, sizeof(t_game));
	(game)->map = malloc(sizeof(t_map));
	if ((game)->map == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		free(game);
		return (NULL);
	}
	ft_memset((game)->map, 0, sizeof(t_map));
	return (game);
}

static void	free_textures(t_game *game)
{
	if (game->map->textures.north != NULL)
		free(game->map->textures.north);
	if (game->map->textures.south != NULL)
		free(game->map->textures.south);
	if (game->map->textures.east != NULL)
		free(game->map->textures.east);
	if (game->map->textures.west != NULL)
		free(game->map->textures.west);
	if (game->map->textures.north_tx != NULL)
		mlx_delete_texture(game->map->textures.north_tx);
	if (game->map->textures.south_tx != NULL)
		mlx_delete_texture(game->map->textures.south_tx);
	if (game->map->textures.east_tx != NULL)
		mlx_delete_texture(game->map->textures.east_tx);
	if (game->map->textures.west_tx != NULL)
		mlx_delete_texture(game->map->textures.west_tx);
}

void	free_game(t_game *game)
{
	if (game == NULL)
		return ;
	if (game->map != NULL)
	{
		free_textures(game);
		if (game->map->map_cpy != NULL)
			ft_free_2d_char(game->map->map_cpy);
		if (game->map->x_row != NULL)
			free(game->map->x_row);
		free(game->map);
	}
	free(game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac == 2)
	{
		game = allocate_memory_for_game();
		if (parser(ac, av, game) == -1)
		{
			free_game(game);
			return (EXIT_FAILURE);
		}
		if (init_max_x(game) == -1 || init_max_y(game) == -1
			|| init_x_row(game) == -1)
		{
			free_game(game);
			return (EXIT_FAILURE);
		}
		init_window(game);
		free_game(game);
	}
	else
		ft_putstr_fd("You need to add a map. \n", 2);
	return (0);
}
