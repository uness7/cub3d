/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:37:45 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/11 10:16:32 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	copy_line(char **dest, char *line)
{
	*dest = ft_strdup(line);
	if (*dest == NULL)
	{
		ft_putstr_fd("Error: memory allocation failed. \n", 2);
		return (-1);
	}
	return (0);
}

static char	**allocate_memory_for_extract_lines(int num_lines)
{
	char	**lines;

	lines = malloc(sizeof(char *) * (num_lines + 1));
	if (lines == NULL)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		return (NULL);
	}
	return (lines);
}

static char	**extract(int fd, char **lines, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (copy_line(&lines[i], line) == -1)
		{
			free(line);
			ft_free_2d_char(lines);
			free_game(game);
			return (NULL);
		}
		free(line);
		i++;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

char	**extract_lines(int fd, char *av, t_game *game)
{
	int		num_lines;
	char	**lines;

	num_lines = count_lines(av);
	if (num_lines == 0 || num_lines == -1)
	{
		ft_putstr_fd("Error: empty map or allocation memory has failed!\n", 2);
		return (NULL);
	}
	lines = allocate_memory_for_extract_lines(num_lines);
	lines = extract(fd, lines, game);
	return (lines);
}
