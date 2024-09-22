/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:05:15 by yzioual           #+#    #+#             */
/*   Updated: 2023/11/03 09:21:54 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size_2d_arr(void **arr)
{
	int		i;

	i = 0;
	if (arr == NULL)
	{
		ft_putstr_fd("Empty 2d array\n", 2);
		exit(EXIT_FAILURE);
	}
	while (arr[i] != NULL)
		i++;
	return (i);
}	