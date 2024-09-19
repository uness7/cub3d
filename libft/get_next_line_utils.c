/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:17:27 by yzioual           #+#    #+#             */
/*   Updated: 2023/11/14 10:25:59 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/get_next_line.h"

char	*ft_strchr_gnl_gnl(char *s, int c)
{
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}



void	*ft_memset_gnl(void *s, int c, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n--)
		*p++ = (unsigned char) c;
	return (s);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (0);
}

char	*ft_strjoin_gnl(char *result, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!result)
	{
		result = (char *)malloc(1 * sizeof(char));
		result[0] = '\0';
	}
	if (!result || !buffer)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen_gnl(result) + ft_strlen_gnl(buffer)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (result)
		while (result[++i] != '\0')
			str[i] = result[i];
	while (buffer[j] != '\0')
		str[i++] = buffer[j++];
	str[ft_strlen_gnl(result) + ft_strlen_gnl(buffer)] = '\0';
	free(result);
	return (str);
}