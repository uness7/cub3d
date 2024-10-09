/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:10:57 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/09 12:10:59 by tblot-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_textures_diff(char **textures)
{
	int	counter;
	int	i;

	counter = 0;
	i = 0;
	while (textures[i] != NULL)
	{
		if (ft_strncmp(textures[i], "NO", 2) == 0)
			counter++;
		else if (ft_strncmp(textures[i], "SO", 2) == 0)
			counter++;
		else if (ft_strncmp(textures[i], "EA", 2) == 0)
			counter++;
		else if (ft_strncmp(textures[i], "WE", 2) == 0)
			counter++;
		i++;
	}
	if (counter == 4)
		return (true);
	ft_putstr_fd("Something wrong with textures\n", 2);
	return (false);
}

bool	is_textures_formats(char **textures)
{
	int		i;
	char	*path;
	char	**split;

	i = -1;
	while (textures[++i] != NULL)
	{
		split = ft_split(textures[i], ' ');
		if (!split || !split[1])
		{
			ft_free_2d_char(split);
			ft_putstr_fd("Something is wrong with the textures\n", 2);
			return (false);
		}
		path = split[1];
		if (check_file_format(path, "png") == false)
		{
			ft_putstr_fd("One of the textures files has invalid format\n", 2);
			ft_free_2d_char(split);
			return (false);
		}
		ft_free_2d_char(split);
	}
	return (true);
}

bool	validate_rgb_values(char *rgb)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(rgb, ',');
	if (!split || !split[0] || !split[1] || !split[2])
	{
		ft_free_2d_char(split);
		ft_putstr_fd("Something wrong with colors\n", 2);
		return (false);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	ft_free_2d_char(split);
	if ((r <= 255 && r >= 0) && (g <= 255 && g >= 0) && (b <= 255 && b >= 0))
		return (true);
	ft_putstr_fd("One or more RGB values is not valid\n", 2);
	return (false);
}

bool	is_valid_colors(char **colors)
{
	int		i;
	char	*rgb;
	char	**split;

	i = -1;
	while (colors[++i] != NULL)
	{
		split = ft_split(colors[i], ' ');
		if (!split || !split[1])
		{
			ft_free_2d_char(split);
			ft_putstr_fd("Something wrong with colors\n", 2);
			return (false);
		}
		rgb = split[1];
		if (!validate_rgb_values(rgb))
		{
			ft_putstr_fd("RGB colors should be within 0 - 255\n", 2);
			ft_free_2d_char(split);
			return (false);
		}
		ft_free_2d_char(split);
	}
	return (true);
}

bool	is_colors_diff(char **colors)
{
	int	counter;
	int	i;

	counter = 0;
	i = -1;
	while (colors[++i])
	{
		if (ft_strncmp(colors[i], "F ", 2) == 0)
			counter++;
		else if (ft_strncmp(colors[i], "C ", 2) == 0)
			counter++;
	}
	if (counter == 2)
		return (true);
	ft_putstr_fd("Floor or Ceiling colors is not valid (maybe both)\n", 2);
	return (false);
}
