/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:57:14 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/14 15:04:15 by yzioual          ###   ########.fr       */
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

static int	helper_fun(char **textures, int *i, t_seen seen)
{
	if (ft_strncmp(textures[*i], "NO", 2) == 0)
	{
		if (seen.no_seen)
			return (-1);
		toggle_bool(&seen.no_seen);
	}
	else if (ft_strncmp(textures[*i], "SO", 2) == 0)
	{
		if (seen.so_seen)
			return (-1);
		toggle_bool(&seen.so_seen);
	}
	else if (ft_strncmp(textures[*i], "EA", 2) == 0)
	{
		if (seen.ea_seen)
			return (-1);
		toggle_bool(&seen.ea_seen);
	}
	else if (ft_strncmp(textures[*i], "WE", 2) == 0)
	{
		if (seen.we_seen)
			return (-1);
		toggle_bool(&seen.we_seen);
	}
	return (0);
}

int	check_double_textures(char **textures)
{
	t_seen	seen;
	int		i;

	seen.no_seen = false;
	seen.so_seen = false;
	seen.ea_seen = false;
	seen.we_seen = false;
	i = -1;
	while (textures[++i] != NULL)
		if (helper_fun(textures, &i, seen) == -1)
			return (-1);
	return (0);
}
