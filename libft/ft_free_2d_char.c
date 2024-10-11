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

void    ft_free_2d_char(char **arr)
{
    int     i;

    i = 0;
    if (arr == NULL)
    {
        ft_putstr_fd("Empty 2d array ft_free_2d_char\n", 2);        
        return ;        
    }
    while (arr[i] != NULL)
    {

        free(arr[i]);
        i++;
    }
    free(arr);
}