/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:51:18 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/14 14:51:18 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * validate_colors - Validates and loads the colors from the copied lines.
 * @game: Pointer to the game structure.
 * @cpy_lines: Array of strings containing colors definitions.
 *
 * Returns 0 on success, -1 on error.
 */

int	validate_colors(t_game *game, char **cpy_lines)
{
	char	**colors;

	colors = NULL;
	if (cpy_lines == NULL)
	{
		ft_putstr_fd("Error: empty 2D array. \n", 2);
		return (-1);
	}
	colors = copy_colors(cpy_lines);
	if (colors == NULL)
		return (-1);
	if (ft_size_2d_arr((void **)colors) == 2 && is_valid_colors(colors)
		&& is_colors_diff(colors))
	{
		load_colors(game, colors);
	}
	else
	{
		ft_putstr_fd("Error: something wrong detected in map\n", 2);
		ft_free_2d_char(colors);
		return (-1);
	}
	ft_free_2d_char(colors);
	return (0);
}

int	parse_map(t_game *game, char **arr)
{
	char	**lines;
	int		num_lines;
	char	**map;

	lines = ft_remove_empty_lines(arr);
	if (lines == NULL)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		return (-1);
	}
	num_lines = ft_size_2d_arr((void **)(lines + 6));
	if (num_lines == 0 || num_lines == -1)
	{
		ft_free_2d_char(lines);
		return (-1);
	}
	map = allocate_map(num_lines);
	if (copy_valid_map(game, map, lines, num_lines) == -1)
		return (-1);
	ft_free_2d_char(lines);
	ft_free_2d_char(map);
	return (0);
}

void	toggle_bool(bool *b)
{
	*b = !(*b);
}
