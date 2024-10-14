/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:51:03 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/14 17:20:00 by yzioual          ###   ########.fr       */
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

static char	**copy_valid_textures(char **textures, char **cpy_lines)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (cpy_lines[++i] != NULL)
	{
		if (is_valid(cpy_lines[i]) == true)
		{
			if (j >= 4 || copy_texture(&textures[j], cpy_lines[i]) == -1)
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

char	**copy_textures(char **cpy_lines)
{
	char	**textures;

	textures = malloc(sizeof(char *) * (NUM_OF_TEXTURES + 1));
	ft_memset(textures, 0, sizeof(char *) * (NUM_OF_TEXTURES + 1));
	if (textures == NULL)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		return (NULL);
	}
	if (check_double_textures(cpy_lines) == -1)
	{
		ft_putstr_fd("Error: double textures were detected in map. \n", 2);
		ft_free_2d_char(textures);
		return (NULL);
	}
	textures = copy_valid_textures(textures, cpy_lines);
	return (textures);
}
