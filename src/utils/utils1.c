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

static char	*get_file_extension(const char *file_path)
{
	char	*dot;

	dot = ft_strrchr(file_path, '.');
	if (!dot || dot == file_path)
		return ("");
	return (dot + 1);
}

bool	check_file_format(const char *file_path, char *format)
{
	char	*file_ext;

	file_ext = get_file_extension(file_path);
	if (ft_strncmp(file_ext, format, ft_strlen(file_ext)) == 0)
		return (true);
	return (false);
}

int	count_lines(char *filename)
{
	int		fd;
	int		num_lines;
	char	*line;

	num_lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: open failed hi\n", 2);
		return (-1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		num_lines++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (num_lines);
}

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

char	**extract_lines(int fd, char *av, t_game *game)
{
	int		i;
	int		num_lines;
	char	*line;
	char	**lines;

	num_lines = count_lines(av);
	if (num_lines == 0 || num_lines == -1)
	{
		ft_putstr_fd("Error: empty map or allocation memory has failed!\n", 2);		
		return (NULL);
	}
	lines = allocate_memory_for_extract_lines(num_lines);
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
