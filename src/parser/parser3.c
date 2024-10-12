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
	return (ft_strncmp(line, "NO", 2) == 0 
		|| ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "EA", 2) == 0 
		|| ft_strncmp(line, "WE", 2) == 0);
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
	return (textures);
}

int		validate_textures(t_game *game, char **cpy_lines)
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
	{
		return (-1);
	}
	if (ft_size_2d_arr((void **)textures) == 4 && is_textures_diff(textures) && is_textures_formats(textures))
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
