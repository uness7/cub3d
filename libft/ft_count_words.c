/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:05:59 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/14 10:06:01 by tblot-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_words_count(char *s)
{
	int	i;
	int	in_word;
	int	count;

	count = 0;
	in_word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] <= 32)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}
