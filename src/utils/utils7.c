/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:57:14 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/11 10:16:16 by yzioual          ###   ########.fr       */
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
