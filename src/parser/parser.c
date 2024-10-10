/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:37:29 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/10 12:37:30 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**allocate_map(int num_lines)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char *) * (num_lines + 1));
	if (map)
	{
		i = -1;
		while (++i <= num_lines)
			map[i] = NULL;
	}
	return (map);
}

static void	cleanup(char **map, int num_lines)
{
	int	i;

	i = -1;
	while (++i < num_lines)
		free(map[i]);
	free(map);
}

static bool	copy_map(char **dest, char **src, int start_index, int num_lines)
{
	int	i;

	i = -1;
	while (++i < num_lines)
	{
		dest[i] = ft_strdup(src[start_index + i]);
		if (!dest[i])
		{
			cleanup(dest, i);
			return (false);
		}
	}
	return (true);
}

void	validate_map_for_parsing(t_game *game, char **map, \
		int num_lines, char **lines)
{
	if (is_map_valid(map, num_lines))
	{
		game->map->map_cpy = allocate_map(num_lines);
		if (!game->map->map_cpy)
		{
			cleanup(map, num_lines);
			ft_free_2d_char(lines);
			return ;
		}
		find_player(game, map);
		load_map(game, map, num_lines);
	}
	cleanup(map, num_lines);
	ft_free_2d_char(lines);
}

void	parse_map(t_game *game, char **arr)
{
	char	**lines;
	int		num_lines;
	char	**map;

	lines = ft_remove_empty_lines(arr);
	if (!lines)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		exit(EXIT_FAILURE);
	}
	num_lines = ft_size_2d_arr((void **)(lines + 6));
	map = allocate_map(num_lines);
	if (!map)
	{
		ft_free_2d_char(lines);
		return ;
	}
	if (!copy_map(map, lines, 6, num_lines))
	{
		cleanup(map, num_lines);
		ft_free_2d_char(lines);
		return ;
	}
	validate_map_for_parsing(game, map, num_lines, lines);
}
