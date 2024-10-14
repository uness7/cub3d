/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:37:02 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/12 13:50:44 by yzioual          ###   ########.fr       */
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
		ft_putstr_fd("Error: ft_strdup has failed. \n", 2);
		return (-1);
	}
	return (0);
}

static bool	is_color(char *color)
{
	return (ft_strncmp(color, "F", 1) == 0 || ft_strncmp(color, "C", 1) == 0);
}

static int	check_double_colors(char **colors)
{
	bool	f_seen;
	bool	c_seen;
	int		i;

	f_seen = false;
	c_seen = false;
	i = 0;
	while (colors[i] != NULL)
	{
		if (ft_strncmp(colors[i], "F", 1) == 0)
		{
			if (f_seen)
				return (-1);
			f_seen = true;
		}
		else if (ft_strncmp(colors[i], "C", 1) == 0)
		{
			if (c_seen)
				return (-1);
			c_seen = true;
		}
		i++;
	}
	return (0);
}

static char	**copy_valid_colors(char **colors, char **cpy_lines)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cpy_lines[++i] != NULL)
	{
		if (is_color(cpy_lines[i]) == true)
		{
			if (copy_color(&colors[j], cpy_lines[i]) == -1)
			{
				colors[j] = NULL;
				ft_free_2d_char(colors);
				return (NULL);
			}
			j++;
		}
	}
	colors[j] = NULL;
	return (colors);
}

char	**copy_colors(char **cpy_lines)
{
	char	**colors;

	colors = malloc(sizeof(char *) * (3 + 1));
	ft_memset(colors, 0, sizeof(char *) * (3 + 1));
	if (colors == NULL)
	{
		ft_putstr_fd("Error: memory allocation had failed\n", 2);
		return (NULL);
	}
	if (check_double_colors(cpy_lines) == -1)
	{
		ft_putstr_fd("Error: double colors in map were detected. \n", 2);
		ft_free_2d_char(colors);
		return (NULL);
	}
	colors = copy_valid_colors(colors, cpy_lines);
	return (colors);
}
