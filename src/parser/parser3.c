/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:37:14 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/10 12:37:15 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid(char *line)
{
	return (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 || ft_strncmp(line, "WE", 2) == 0);
}

static int	copy_texture(char **dest, char *line)
{
	if (line == NULL)
		return (-1);
	*dest = ft_strdup(line);
	if (*dest == NULL)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		return (-1);
	}
	return (0);
}

static int	check_double_textures(char **textures)
{
	bool	no_seen;
	bool	so_seen;
	bool	ea_seen;
	bool	we_seen;
	int		i;

	no_seen = false;
	so_seen = false;
	ea_seen = false;
	we_seen = false;
	i = 0;
	while (textures[i] != NULL)
	{
		if (ft_strncmp(textures[i], "NO", 2) == 0)
		{
			if (no_seen)
				return (-1);
			no_seen = true;
		}
		else if (ft_strncmp(textures[i], "SO", 2) == 0)
		{
			if (so_seen)
				return (-1);
			so_seen = true;
		}
		else if (ft_strncmp(textures[i], "EA", 2) == 0)
		{
			if (ea_seen)
				return (-1);
			ea_seen = true;
		}
		else if (ft_strncmp(textures[i], "WE", 2) == 0)
		{
			if (we_seen)
				return (-1);
			we_seen = true;
		}
		i++;
	}
	return (0);
}

static char	**copy_textures(char **cpy_lines)
{
	int		i;
	int		j;
	char	**textures;

	textures = malloc(sizeof(char *) * (NUM_OF_TEXTURES + 1));
	ft_memset(textures, 0, sizeof(char *) * (NUM_OF_TEXTURES + 1));
	if (textures == NULL)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		return (NULL);
	}
	i = -1;
	j = 0;
	if (check_double_textures(cpy_lines) == -1)
	{
		ft_putstr_fd("Error: double textures were detected in map. \n", 2);
		ft_free_2d_char(textures);
		return (NULL);
	}
	while (cpy_lines[++i] != NULL)
	{
		if (is_valid(cpy_lines[i]) == true)
		{
			if (copy_texture(&textures[j], cpy_lines[i]) == -1)
			{
				ft_free_2d_char(textures);
				return (NULL);
			}
			j++;
		}
	}
	textures[j] = NULL;
	return (textures);
}

int	validate_textures(t_game *game, char **cpy_lines)
{
	char	**textures;

	textures = NULL;
	if (cpy_lines == NULL)
	{
		ft_putstr_fd("Error: empty 2D array. \n", 2);
		return (-1);
	}
	textures = copy_textures(cpy_lines);
	if (textures == NULL)
		return (-1);
	if (ft_size_2d_arr((void **)textures) == 4 && is_textures_diff(textures)
		&& is_textures_formats(textures))
	{
		if (get_textures(game, textures) == -1)
		{
			ft_free_2d_char(textures);
			return (-1);
		}
		load_textures(game);
	}
	else
	{
		ft_putstr_fd("Error: something wrong was detected in map!\n", 2);
		ft_free_2d_char(textures);
		return (-1);
	}
	ft_free_2d_char(textures);
	return (0);
}
