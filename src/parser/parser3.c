/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:37:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/14 16:12:46 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_and_load_textures(t_game *game, char **textures)
{
	if (ft_size_2d_arr((void **)textures) == 4 && is_textures_diff(textures)
		&& is_textures_formats(textures))
	{
		if (get_textures(game, textures) == -1)
		{
			ft_free_2d_char(textures);
			return (-1);
		}
		load_textures(game);
	}
	else
	{
		ft_putstr_fd("Error: something wrong was detected in map!\n", 2);
		ft_free_2d_char(textures);
		return (-1);
	}
	return (0);
}

int	validate_textures(t_game *game, char **cpy_lines)
{
	char	**textures;

	textures = NULL;
	if (cpy_lines == NULL)
	{
		ft_putstr_fd("Error: empty 2D array. \n", 2);
		return (-1);
	}
	textures = copy_textures(cpy_lines);
	if (textures == NULL)
		return (-1);
	if (get_and_load_textures(game, textures) == -1)
		return (-1);
	ft_free_2d_char(textures);
	return (0);
}
