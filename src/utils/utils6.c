/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:39:04 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/10 12:39:07 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	exit_on_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(EXIT_FAILURE);
}

static char	**allocate_result_array(int num_lines)
{
	char	**result;

	result = malloc(sizeof(char *) * (num_lines + 1));
	if (result == NULL)
		exit_on_error("malloc failed\n");
	return (result);
}

static void	free_result_on_error(char **result, int j)
{
	while (j > 0)
		free(result[--j]);
	free(result);
}

static void	copy_non_empty_lines(char **result, char **cpy_lines, int num_lines)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < num_lines && cpy_lines[i] != NULL)
	{
		if (ft_strncmp(cpy_lines[i], "\n", 1) != 0 && cpy_lines[i][0] != '\0')
		{
			result[j] = ft_strdup(cpy_lines[i]);
			if (result[j] == NULL)
				free_result_on_error(result, j);
			j++;
		}
		i++;
	}
	result[j] = NULL;
}

char	**ft_remove_empty_lines(char **cpy_lines)
{
	int		num_lines;
	char	**result;

	if (cpy_lines == NULL)
		exit_on_error("Empty arr\n");
	num_lines = ft_size_2d_arr((void **)cpy_lines);
	if (num_lines == 0)
		exit_on_error("Empty lines detected\n");
	result = allocate_result_array(num_lines);
	copy_non_empty_lines(result, cpy_lines, num_lines);
	return (result);
}

/*
void	print_game_data(t_game *game)
{
	ft_putstr_fd("Printing floor colors: \n", 1);
	printf("R value : %d\n", game->map->floor.r);
	printf("G value : %d\n", game->map->floor.g);
	printf("B value : %d\n", game->map->floor.b);
	printf("RGB value : %d\n", game->map->floor.rgb);
	printf("\n");
	ft_putstr_fd("Printing ceiling colors: \n", 1);
	printf("R value : %d\n", game->map->ceiling.r);
	printf("G value : %d\n", game->map->ceiling.g);
	printf("B value : %d\n", game->map->ceiling.b);
	printf("RGB value : %d\n", game->map->ceiling.rgb);
	printf("\n");
	printf("NO Texture %s\n", game->map->textures.north);
	printf("SO Texture %s\n", game->map->textures.south);
	printf("EA Texture %s\n", game->map->textures.east);
	printf("WE Texture %s\n", game->map->textures.west);
	printf("\n");
	if (game->map->map_cpy != NULL)
		ft_put2d_char(game->map->map_cpy);
	printf("\n");
	if (game->player.orientation == NORTH)
		printf("Player's orientation is north\n");
	if (game->player.orientation == SOUTH)
		printf("Player's orientation is south\n");
	if (game->player.orientation == EAST)
		printf("Player's orientation is east\n");
	if (game->player.orientation == WEST)
		printf("Player's orientation is west\n");
	printf("Player's x coordinates: %f\n", game->player.x);
	printf("Player's y coordinates: %f\n", game->player.y);
	printf("Player's angle: %f\n", game->player.angle);
	printf("Player's rd_fov: %f\n", game->player.rd_fov);
	printf("Player's ws: %d\n", game->player.ws);
	printf("Player's as: %d\n", game->player.ad);
}
*/
