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

void	parse_textures_colors(char **lines, t_game *game)
{
	char	**cpy_lines;

	cpy_lines = lines;
	cpy_lines = ft_remove_empty_lines(cpy_lines);
	if (cpy_lines == NULL)
		exit(EXIT_FAILURE);
	validate_textures(game, cpy_lines);
	validate_colors(game, cpy_lines);
	ft_free_2d_char(cpy_lines);
}

int	parser(__attribute__((unused)) int ac, char **av, t_game *game)
{
	int		fd;
	char	**lines;

	if (check_file_format(av[1], "cub"))
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("Error: open failed. \n", 2);
			return (-1);
		}
		lines = extract_lines(fd, av[1]);
		if (lines == NULL)
			return (-1);
		parse_textures_colors(lines, game);
		parse_map(game, lines);
		ft_free_2d_char(lines);
		close(fd);
	}
	else
	{
		ft_putstr_fd("bad format\n", 2);
		return (-1);
	}
	return (0);
}
