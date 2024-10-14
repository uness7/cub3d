/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 09:24:53 by yzioual           #+#    #+#             */
/*   Updated: 2024/10/14 15:41:48 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_words_count(const char *s, char delim)
{
	int	i;
	int	in_word;
	int	count;

	if (s == NULL)
		return (-1);
	count = 0;
	i = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] <= 32 || s[i] == delim)
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

char	**helper(t_split_fun *split, const char *s, char delim)
{
	int		i;
	int		k;;
	
	i = 0;
	k = -1;
	split->temp = 0;
	while (++k < split->words_count)
	{
		while (s[i] && (s[i] <= 32 || s[i] == delim))
			i++;
		split->start = i;
		while (s[i] && s[i] > 32 && s[i] != delim)
			i++;
		split->word_len = i - split->start;
		split->result[k] = malloc(sizeof(char) * (split->word_len + 1));
		if (split->result[k] == NULL)
			return (NULL);
		split->temp = -1;
		while (++split->temp < split->word_len)
			split->result[k][split->temp] = s[split->start + split->temp];
		split->result[k][split->temp] = '\0';
	}
	split->result[split->words_count] = NULL;
	return (split->result);
}

char	**ft_split(const char *s, char delim)
{
	t_split_fun	split;

	if (s == NULL)
		return (NULL);
	split.words_count = ft_words_count(s, delim);
	split.result = malloc(sizeof(char *) * (split.words_count + 1));
	if (split.result == NULL)
		return (NULL);
	/*
	split.temp = 0;
	while (++k < split.words_count)
	{
		while (s[i] && (s[i] <= 32 || s[i] == delim))
			i++;
		split.start = i;
		while (s[i] && s[i] > 32 && s[i] != delim)
			i++;
		split.word_len = i - split.start;
		split.result[k] = malloc(sizeof(char) * (split.word_len + 1));
		if (split.result[k] == NULL)
			return (NULL);
		split.temp = -1;
		while (++split.temp < split.word_len)
			split.result[k][split.temp] = s[split.start + split.temp];
		split.result[k][split.temp] = '\0';
	}
	split.result[split.words_count] = NULL;
	*/
	char **result = NULL; 
	result = helper(&split, s, delim);
	return (result);
}
