/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:58:50 by yzioual           #+#    #+#             */
/*   Updated: 2023/11/14 10:15:04 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

void	*ft_memset_gnl(void *str, int c, size_t n);
char	*get_next_line(int fd);
char	*ft_read_data(int fd, char *result);
char	*ft_update_buffer(char *buffer);
char	*ft_extract_line(char *buffer);
char	*ft_strjoin_gnl(char *dest, char *src);
char	*ft_strchr_gnl(char *s, int c);

size_t	ft_strlen_gnl(const char *str);

#endif
