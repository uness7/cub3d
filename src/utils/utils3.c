/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:38:00 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/10 12:38:04 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_composed_of_valid_chars(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'N'
				&& map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E'
				&& map[i][j] != ' ' && map[i][j] != '\n')
			{
				ft_putstr_fd("Map is composed of multi valid chars\n", 2);
				return (false);
			}
		}
	}
	return (true);
}

bool	check_first_nd_last_rows(char **map, int rows)
{
	int	i;
	int	j;
	int	len;

	j = 0;
	i = -1;
	while (++i < rows)
	{
		j = 0;
		len = ft_strlen(map[i]);
		while (j < len && ft_isspace(map[i][j]))
			j++;
		if (i == 0 || i == rows - 1)
		{
			while (j <= len - 1)
			{
				if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\n')
					return (false);
				j++;
			}
		}
	}
	return (true);
}

static bool	is_char_repeated(char **map, int rows)
{
	int	i;
	int	j;
	int	len;
	int	counter;

	j = 0;
	i = -1;
	counter = 0;
	while (++i < rows)
	{
		j = 0;
		len = ft_strlen(map[i]);
		while (j <= len - 1)
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				counter++;
			j++;
		}
	}
	if (counter == 0 || counter != 1)
		return (false);
	return (true);
}

bool	has_multi_valid_chars(char **map, int rows)
{
	if (!is_char_repeated(map, rows))
	{
		ft_putstr_fd("Map has multi or zero valid chars\n", 2);
		return (false);
	}
	return (true);
}
