/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:37:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/10 12:37:10 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	copy_color(char **dest, char *line)
{
	if (line == NULL)
		return (-1);
	*dest = ft_strdup(line);
	if (*dest == NULL)
	{
		ft_putstr_fd("Error: ft_strdup failed. \n", 2);
		free(dest);
		return (-1);
	}
	return (0);
}

static bool	is_color(char *color)
{
	return (ft_strncmp(color, "F", 1) == 0 || ft_strncmp(color, "C", 1) == 0);
}

static char	**copy_colors(char **cpy_lines)
{
	char	**colors;
	int		i;
	int		j;

	i = -1;
	j = 0;
	colors = malloc(sizeof(char *) * NUM_OF_RGB_VALUES);
	if (colors == NULL)
	{
		ft_putstr_fd("Error: memory allocation had failed\n", 2);
		return (NULL);
	}
	while (cpy_lines[++i] != NULL)
	{
		if (is_color(cpy_lines[i]) == true)
		{
			if (copy_color(&colors[j], cpy_lines[i]) == -1)
			{
				ft_free_2d_char(colors);
				return (NULL);
			}
			j++;
		}
	}
	colors[j] = NULL;
	return (colors);
}

int	validate_colors(t_game *game, char **cpy_lines)
{
	char	**colors;

	colors = copy_colors(cpy_lines);
	if (colors == NULL)
	{
		return (-1);
	}
	if (ft_size_2d_arr((void **)colors) == 2 \
			&& is_valid_colors(colors) \
			&& is_colors_diff(colors))
	{
		load_colors(game, colors);
		ft_free_2d_char(colors);
	}
	else
	{
		ft_putstr_fd("Error: something wrong detected in map\n", 2);
		ft_free_2d_char(colors);
		return (-1);
	}
	return (0);
}
