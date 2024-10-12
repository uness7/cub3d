/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:42:47 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/12 11:41:17 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_x_row(t_game *game)
{
	int	i;
	int	j;

	game->map->x_row = malloc(sizeof(int) * (game->map->max_y + 1));
	if (game->map->x_row == NULL)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		return (-1);
	}
	i = 0;
	j = 0;
	while (game->map->map_cpy[i] != NULL)
	{
		game->map->x_row[j] = ft_strlen(game->map->map_cpy[i]);
		i++;
		j++;
	}
	return (0);
}

int	init_max_y(t_game *game)
{
	int	i;

	if (game == NULL)
	{
		ft_putstr_fd("Error: game structure is emtpy :, \n", 2);
		return (-1);
	}
	i = 0;
	while (game->map->map_cpy[i] != NULL)
		i++;
	game->map->max_y = i;
	return (0);
}

int	init_max_x(t_game *game)
{
	int	i;
	int	len;

	if (game == NULL)
	{
		ft_putstr_fd("Error: game structure is emtpy :, \n", 2);
		return (-1);
	}
	i = 0;
	len = 0;
	game->map->max_x = 0;
	if (game->map->map_cpy == NULL)
	{
		ft_putstr_fd("Error: error in map is detected. \n", 2);
		return (-1);
	}
	while (game->map->map_cpy[i] != NULL)
	{
		len = ft_strlen(game->map->map_cpy[i]);
		if ((unsigned int)len > game->map->max_x)
			game->map->max_x = len;
		i++;
	}
	return (0);
}

bool	check_hit(t_game *game, double x, double y)
{
	unsigned int	x_m;
	unsigned int	y_m;

	if (x < 0 || y < 0)
		return (true);
	x_m = (unsigned int)floor(x / TILESIZE);
	y_m = (unsigned int)floor(y / TILESIZE);
	if ((y_m >= game->map->max_y || x_m >= game->map->x_row[y_m]))
		return (true);
	if (game->map->map_cpy[(int)y_m])
	{
		if (game->map->map_cpy[(int)y_m][(int)x_m])
		{
			if (game->map->map_cpy[(int)y_m][(int)x_m] == '1')
				return (true);
		}
	}
	return (false);
}
