/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:57:14 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/11 10:08:24 by tblot-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**allocate_memory_for_extract_lines(t_game *game, int num_lines)
{
	char	**lines;

	lines = malloc(sizeof(char *) * (num_lines + 1));
	if (lines == NULL)
	{
		ft_putstr_fd("Error: memory allocation has failed. \n", 2);
		exit(EXIT_FAILURE);
	}
	return (lines);
}
