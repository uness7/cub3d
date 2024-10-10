/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:36:37 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/10 12:36:41 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	assign_texture(char **dest, const char *path)
{
	*dest = ft_strdup(path);
	if (dest == NULL)
	{
		ft_putstr_fd("Error: ft_stdup has failed\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	get_textures(t_game *game, char **textures)
{
	int		i;
	char	**split;

	i = -1;
	while (textures[++i] != NULL)
	{
		split = ft_split(textures[i], ' ');
		if (!split || !split[0] || !split[1])
		{
			ft_free_2d_char(split);
			ft_putstr_fd("Something is wrong with the textures\n", 2);
			exit(EXIT_FAILURE);
		}
		if (ft_strncmp(split[0], "NO", 2) == 0)
			assign_texture(&game->map->textures.north, split[1]);
		if (ft_strncmp(split[0], "SO", 2) == 0)
			assign_texture(&game->map->textures.south, split[1]);
		if (ft_strncmp(split[0], "EA", 2) == 0)
			assign_texture(&game->map->textures.east, split[1]);
		if (ft_strncmp(split[0], "WE", 2) == 0)
			assign_texture(&game->map->textures.west, split[1]);
		ft_free_2d_char(split);
	}
}
