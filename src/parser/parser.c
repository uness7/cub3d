# include "../../inc/cub3d.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	count_lines(char *filename)
{
	int		fd;
	int 		num_lines;
	char	*line;

	num_lines = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0) {
		perror("open failed");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL) {
		num_lines++;
		free(line);
	}
	close(fd);
	return num_lines;
}


static char	**extract_lines(int fd, char *av)
{
	int		i;
	int		num_lines;
	char	*line;
	char	**lines;

	num_lines = count_lines(av);
	lines = malloc(sizeof(char *) * (num_lines + 1));
	if (lines == NULL)
	{
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		lines[i] = ft_strdup(line);
		free(line);
		i++;
	}
	lines[i] = NULL;
	close(fd);
	return (lines);
}

void	parser(int ac, char **av)
{
	int	fd;
	(void)ac;

	if (check_file_format(av[1], "cub"))
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("open failed. \n", 2);
			exit(EXIT_FAILURE);
		}
		char	**lines = extract_lines(fd, av[1]);
		ft_putstr_fd(*lines, 1);
	}
	else
		ft_putstr_fd("bad format\n", 2);
}
