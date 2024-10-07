/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 10:39:37 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/05 10:43:13 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	allocate_memory_for_game(t_game **game)
{
	*game = malloc(sizeof(t_game));
	if (*game == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_memset(*game, 0, sizeof(t_game));
	(*game)->map = malloc(sizeof(t_map));
	if ((*game)->map == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_memset((*game)->map, 0, sizeof(t_map));
}

void	free_game(t_game *game)
{
	free(game->map->textures.north);
	free(game->map->textures.south);
	free(game->map->textures.east);
	free(game->map->textures.west);
	mlx_delete_texture(game->map->textures.north_tx);
	mlx_delete_texture(game->map->textures.south_tx);
	mlx_delete_texture(game->map->textures.east_tx);
	mlx_delete_texture(game->map->textures.west_tx);
	ft_free_2d_char(game->map->map_cpy);
	free(game->map->x_row);
	free(game->map);
	free(game);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac == 2)
	{
		allocate_memory_for_game(&game);
		if (parser(ac, av, game) != 0)
		{
			free(game->map);
			free(game);
			return (EXIT_FAILURE);
		}
		init_max_x(game);
		init_max_y(game);
		init_x_row(game);
		init_window(game);
		free_game(game);
        /*
        print_game_data(game);
        */
	}
	else
		ft_putstr_fd("You need to add a map :(\n", 2);
	return (0);
}
