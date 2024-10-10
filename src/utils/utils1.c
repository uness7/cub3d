#include "../../inc/cub3d.h"

static char	*get_file_extension(const char *file_path)
{
	char	*dot;

	dot = ft_strrchr(file_path, '.');
	if (!dot || dot == file_path)
		return ("");
	return (dot + 1);
}

bool	check_file_format(const char *file_path, char *format)
{
	char	*file_ext;

	file_ext = get_file_extension(file_path);
	if (ft_strncmp(file_ext, format, ft_strlen(file_ext)) == 0)
		return (true);
	return (false);
}

int	count_lines(char *filename)
{
	int		fd;
	int		num_lines;
	char	*line;

	num_lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		return (-1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = get_next_line(fd);
		num_lines++;
		free(line);
	}
	free(line);
	close(fd);
	return (num_lines);
}

void	copy_line(char **dest, char *line)
{
	*dest = ft_strdup(line);
	if (*dest == NULL)
	{
		ft_putstr_fd("Error: memory allocation failed. \n", 2);
		exit(EXIT_FAILURE);
	}
}

char	**extract_lines(int fd, char *av)
{
	int		i;
	int		num_lines;
	char	*line;
	char	**lines;

	num_lines = count_lines(av);
	lines = malloc(sizeof(char *) * (num_lines + 1));
	if (num_lines == 0 || num_lines == -1 || lines == NULL)
	{
		ft_putstr_fd("Empty map or allocation memory has failed!\n", 2);
		return (NULL);
	}
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		copy_line(&lines[i], line);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

/*
char	**ft_remove_empyt_lines(char **cpy_lines)
{
	int		i;
	int		j;
	int		num_lines;
	char	**result;

	if (cpy_lines == NULL)
	{
		ft_putstr_fd("Empty arr\n", 2);
		exit(EXIT_FAILURE);
	}
	num_lines = ft_size_2d_arr((void **)cpy_lines);
	if (num_lines == 0)
	{
		ft_putstr_fd("Empty lines detected\n", 2);
		exit(EXIT_FAILURE);
	}
	result = malloc(sizeof(char *) * (num_lines + 1));
	if (result == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	while (cpy_lines[i] != NULL)
	{
		if (ft_strncmp(cpy_lines[i], "\n", 1) != 0 && cpy_lines[i][0] != '\0')
		{
			result[j] = ft_strdup(cpy_lines[i]);
			if (result[j] == NULL)
			{
				ft_putstr_fd("ft_strdup failed\n", 2);
				while (j > 0)
					free(result[--j]);
				free(result);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}
*/
