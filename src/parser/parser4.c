/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:36:57 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/11 10:16:42 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_textures_colors(char **lines, t_game *game)
{
	char	**cpy_lines;

	cpy_lines = lines;
	cpy_lines = ft_remove_empty_lines(cpy_lines);
	if (cpy_lines == NULL)
	{
		ft_free_2d_char(cpy_lines);
		return (-1);
	}
	if (validate_textures(game, cpy_lines) == -1)
	{
		ft_free_2d_char(cpy_lines);
		return (-1);
	}
	if (validate_colors(game, cpy_lines) == -1)
	{
		ft_free_2d_char(cpy_lines);
		return (-1);
	}
	ft_free_2d_char(cpy_lines);
	return (0);
}

int	parser(__attribute__((unused)) int ac, char **av, t_game *game)
{
	int		fd;
	char	**lines;

	if (!check_file_format(av[1], "cub"))
	{
		ft_putstr_fd("bad format\n", 2);
		return (-1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: open failed. \n", 2);
		return (-1);
	}
	lines = extract_lines(fd, av[1], game);
	if (lines == NULL || parse_textures_colors(lines, game) == -1
		|| parse_map(game, lines) == -1)
	{
		ft_free_2d_char(lines);
		return (-1);
	}
	ft_free_2d_char(lines);
	close(fd);
	return (0);
}
