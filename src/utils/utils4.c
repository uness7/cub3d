/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:38:08 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/10 12:38:15 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	check_first_nd_last_char(char **map, int rows)
{
	int	i;
	int	j;
	int	len;
	int	last;

	i = -1;
	j = 0;
	while (++i < rows)
	{
		j = 0;
		len = ft_strlen(map[i]);
		while (map[i][j] == ' ')
			j++;
		if (map[i][j] != '1')
			return (false);
		last = len - 1;
		while (last >= 0 && (map[i][last] == ' ' || map[i][last] == '\n'))
			last--;
		if (map[i][last] != '1')
			return (false);
	}
	return (true);
}

bool	check_adjacent_to_spaces(char **map, int rows)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < rows)
	{
		len = ft_strlen(map[i]);
		j = 1;
		while (j < len - 1)
		{
			if (map[i][j] == ' ')
			{
				if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
					return (false);
				if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
					return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_row_longer_than_top(char **map, int rows)
{
	int	i;
	int	j;
	int	len_curr;
	int	len_top;

	i = 0;
	while (++i < rows)
	{
		len_curr = ft_strlen(map[i]);
		len_top = ft_strlen(map[i - 1]);
		if (map[i][len_curr - 1] == '\n')
			len_curr--;
		if (map[i - 1][len_top - 1] == '\n')
			len_top--;
		if (len_curr > len_top)
		{
			j = len_top - 1;
			while (++j < len_curr)
			{
				if (map[i][j] != '1' && map[i][j] != ' ')
					return (false);
			}
		}
	}
	return (true);
}

bool	is_map_valid(char **map, int num_lines)
{
	return (is_composed_of_valid_chars(map) && has_multi_valid_chars(map,
			num_lines) && check_first_nd_last_rows(map, num_lines)
		&& check_first_nd_last_char(map, num_lines)
		&& check_adjacent_to_spaces(map, num_lines)
		&& check_row_longer_than_top(map, num_lines)
		&& check_row_longer_than_bottom(map, num_lines));
}
