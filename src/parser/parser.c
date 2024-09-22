#include "../../inc/cub3d.h"
#include <stdio.h>

// IsFull = false;

static void	validate_colors(char **cpy_lines)
{
	char	**colors;
	int		i;
	int		j;

	i = -1;
	colors = malloc(sizeof(char *) * 3);
	if (colors == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (cpy_lines[++i] != NULL)
	{
		if (ft_strncmp(cpy_lines[i], "F", 1) == 0 || ft_strncmp(cpy_lines[i], "C", 1) == 0)
			colors[j++] = ft_strdup(cpy_lines[i]);
	}
	colors[j] = NULL;
	if (ft_size_2d_arr((void **)colors) == 2 && is_valid_colors(colors) && is_colors_diff(colors))
	{
		// filling colors struct here
		ft_putstr_fd("printing colors: \n", 1);
		ft_put2d_char(colors);
	}
	else
	{
		ft_putstr_fd("Error detected in map\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_free_2d_char(colors);
}

static void	validate_textures(char **cpy_lines)
{
	char	**textures;
	int		i;
	int		j;

	i = -1;
	if (cpy_lines == NULL)
	{
		ft_putstr_fd("Empty 2D array\n", 2);
		exit(EXIT_FAILURE);
	}
	textures = malloc(sizeof(char *) * 5);
	if (textures == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (cpy_lines[++i] != NULL)
	{
		if (ft_strncmp(cpy_lines[i], "NO", 2) == 0\
				|| ft_strncmp(cpy_lines[i], "SO", 2) == 0\
				|| ft_strncmp(cpy_lines[i], "EA", 2) == 0\
				|| ft_strncmp(cpy_lines[i], "WE", 2) == 0)
		{
			textures[j++] = ft_strdup(cpy_lines[i]);			
		}
	}
	textures[j] = NULL;
	if (ft_size_2d_arr((void **)textures) == 4 \
			&& is_textures_diff(textures)
			&& is_textures_formats(textures))
	{
		// filling the struct t_texture here
		printf("printing textures: \n");
		ft_put2d_char(textures);
	}
	else
	{
	
		ft_putstr_fd("Error detected in map!\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_free_2d_char(textures);
}

void	parse_textures_colors(char **lines /*, t_game *game*/)
{
	char	**cpy_lines;

	cpy_lines = lines;
	cpy_lines = ft_remove_empyt_lines(cpy_lines);	
	validate_textures(cpy_lines);
	validate_colors(cpy_lines);
	ft_free_2d_char(cpy_lines);
}

void	parse_map(char **arr)
{
	int		i;
	int		j;
	int		num_lines;
	char	**map;
	char	**lines;

	i = 5;
	j = 0;
	lines = ft_remove_empyt_lines(arr);
	num_lines = ft_size_2d_arr((void **)(lines + 6));
	map = malloc(sizeof(char *) * (num_lines + 1));
	if (map == NULL)
		exit(EXIT_FAILURE);
	while (lines[++i] != NULL)
		map[j++] = ft_strdup(lines[i]);
	map[j] = NULL;
	//printf("num of lines : %d\n", num_lines);
	if (is_map_valid(map, num_lines))
	{
		ft_putstr_fd("Wow, I love nvim config\n", 1);
		printf("Printing the map: \n");
		ft_put2d_char(map);
	}
}

void	parser(__attribute__((unused)) int ac, char **av)
{
	int		fd;
	char	**lines;
	
	// ft_memset(game, 0, sizeof(t_game));
	if (check_file_format(av[1], "cub"))
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("open failed. \n", 2);
			exit(EXIT_FAILURE);
		}
		lines = extract_lines(fd, av[1]);
		parse_textures_colors(lines);
		parse_map(lines);
		ft_free_2d_char(lines);
		close(fd);
	}
	else
		ft_putstr_fd("bad format\n", 2);
}
