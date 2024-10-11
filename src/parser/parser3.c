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

static void	copy_texture(char **dest, char *line)
{
	*dest = ft_strdup(line);
	if (*dest == NULL)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		ft_free_2d_char(dest);
		exit(EXIT_FAILURE);
	}
}

static char	**copy_textures(char **cpy_lines)
{
	int		i;
	int		j;
	char	**textures = malloc(sizeof(char *) * (NUM_OF_TEXTURES+1));

	i = -1;
	j = 0;
	while (cpy_lines[++i] != NULL)
	{
		if (is_valid(cpy_lines[i]))
		{
			copy_texture(&textures[j], cpy_lines[i]);
			j++;
		}
	}
	return (textures);
}

void	validate_textures(t_game *game, char **cpy_lines)
{
	char	**textures;

	if (cpy_lines == NULL)
	{
		ft_putstr_fd("Error: empty 2D array. \n", 2);
		exit(EXIT_FAILURE);
	}
	textures = copy_textures(cpy_lines);
	if (ft_size_2d_arr((void **)textures) == 4 \
		&& is_textures_diff(textures) \
		&& is_textures_formats(textures))
	{
		get_textures(game, textures);
		load_textures(game);
	}
	else
	{
		ft_putstr_fd("Error detected in map!\n", 2);
		ft_free_2d_char(textures);
		free_game(game);
		exit(EXIT_FAILURE);
	}
	ft_free_2d_char(textures);
}
