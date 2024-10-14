/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzioual <yzioual@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:28:52 by yzioual           #+#    #+#             */
/*   Updated: 2023/11/14 12:45:33 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../inc/get_next_line.h"

char	*ft_update_buffer(char *buffer)
{
	char	*new_buffer;
	int		len;
	int		j;

	len = 0;
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	if (!buffer[len])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(sizeof(char) * (ft_strlen_gnl(buffer) - len + 1));
	if (!new_buffer)
		return (NULL);
	len++;
	j = 0;
	while (buffer[len])
		new_buffer[j++] = buffer[len++];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*ft_extract_line(char *buffer)
{
	char	*line;
	int		len;

	len = 0;
	if (!buffer[len])
		return (NULL);
	while (buffer[len] != '\0' && buffer[len] != '\n')
		len++;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
	{
		line[len] = buffer[len];
		len++;
	}
	if (buffer[len] == '\n')
	{
		line[len] = buffer[len];
		len++;
	}
	line[len] = '\0';
	return (line);
}

char	*ft_read_data(int fd, char *result)
{
	char	*buffer;
	int		bytes;	

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	ft_memset_gnl(buffer, 0, BUFFER_SIZE);
	while (!ft_strchr_gnl(buffer, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(result);
			return (NULL);
		}
		buffer[bytes] = '\0';
		result = ft_strjoin_gnl(result, buffer);
	}
	free(buffer);
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_read_data(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	result = ft_extract_line(buffer);
	buffer = ft_update_buffer(buffer);
	return (result);
}

/*
int	main(void)
{
	int	fd = open("test.txt", O_RDONLY);
	char	*line;

	if (fd == -1)
	{
		perror("Err");
		return 1;
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
