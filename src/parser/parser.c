#include "../../inc/cub3d.h"

static void	validate_colors(t_game *game, char **cpy_lines)
{
	char	**colors;
	int		i;
	int		j;

	i = -1;
	colors = malloc(sizeof(char *) * NUM_OF_RGB_VALUES);
	if (colors == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (cpy_lines[++i] != NULL)
	{
		if (ft_strncmp(cpy_lines[i], "F", 1) == 0 || ft_strncmp(cpy_lines[i],
				"C", 1) == 0)
		{
			colors[j] = ft_strdup(cpy_lines[i]);
			if (colors[j] == NULL)
			{
				perror("ft_strdup failed");
				while (j > 0)
					free(colors[--j]);
				free(colors);
				exit(EXIT_FAILURE);
			}
			j++;
		}
	}
	colors[j] = NULL;
	if (ft_size_2d_arr((void **)colors) == 2 && is_valid_colors(colors)
		&& is_colors_diff(colors))
	{
		load_colors(game, colors);
		ft_free_2d_char(colors);
	}
	else
	{
		ft_putstr_fd("Error detected in map\n", 2);
		ft_free_2d_char(colors);
		exit(EXIT_FAILURE);
	}
}

static void	validate_textures(t_game *game, char **cpy_lines)
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
	textures = malloc(sizeof(char *) * (NUM_OF_TEXTURES + 1));
	if (textures == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	j = 0;
	while (cpy_lines[++i] != NULL)
	{
		if (ft_strncmp(cpy_lines[i], "NO", 2) == 0 || ft_strncmp(cpy_lines[i],
				"SO", 2) == 0 || ft_strncmp(cpy_lines[i], "EA", 2) == 0
			|| ft_strncmp(cpy_lines[i], "WE", 2) == 0)
		{
			textures[j] = ft_strdup(cpy_lines[i]);
			if (textures[j] == NULL)
			{
				perror("ft_strdup failed");
				while (j > 0)
					free(textures[--j]);
				free(textures);
				exit(EXIT_FAILURE);
			}
			j++;
		}
	}
	textures[j] = NULL;
	if (ft_size_2d_arr((void **)textures) == 4 && is_textures_diff(textures)
		&& is_textures_formats(textures))
	{
		get_textures(game, textures);
		load_textures(game);
	}
	else
	{
		ft_putstr_fd("Error detected in map!\n", 2);
		ft_free_2d_char(textures);
		exit(EXIT_FAILURE);
	}
	ft_free_2d_char(textures);
}

void	parse_textures_colors(char **lines, t_game *game)
{
	char	**cpy_lines;

	cpy_lines = lines;
	cpy_lines = ft_remove_empyt_lines(cpy_lines);
	if (cpy_lines == NULL)
		exit(EXIT_FAILURE);
	validate_textures(game, cpy_lines);
	validate_colors(game, cpy_lines);
	ft_free_2d_char(cpy_lines);
}

void	parse_map(t_game *game, char **arr)
{
	int		i;
	int		j;
	int		num_lines;
	char	**map;
	char	**lines;

	i = 5;
	j = 0;
	lines = ft_remove_empyt_lines(arr); // what happens to arr ??
	num_lines = ft_size_2d_arr((void **)(lines + 6));
	map = malloc(sizeof(char *) * (num_lines + 1));
	if (map == NULL)
		exit(EXIT_FAILURE);
	while (lines[++i] != NULL)
	{
		map[j] = ft_strdup(lines[i]);
		if (map[j] == NULL)
		{
			while (j > 0)
				free(map[--j]);
			free(map);
			ft_free_2d_char(lines);
			exit(EXIT_FAILURE);
		}
		j++;
	}
	map[j] = NULL;
	if (is_map_valid(map, num_lines))
	{
		game->map->map_cpy = malloc(sizeof(char *) * (num_lines + 1));
		if (game->map->map_cpy == NULL)
			exit(EXIT_FAILURE);
		find_player(game, map);
		load_map(game, map, num_lines);
	}
	ft_free_2d_char(map);
	ft_free_2d_char(lines);
}

int	parser(__attribute__((unused)) int ac, char **av, t_game *game)
{
	int		fd;
	char	**lines;

	if (check_file_format(av[1], "cub"))
	{
		fd = open(av[1], O_RDONLY);
		if (fd < 0)
		{
			ft_putstr_fd("open failed. \n", 2);
			return (-1);
		}
		lines = extract_lines(fd, av[1]);
		if (lines == NULL)
			return (-1);
		parse_textures_colors(lines, game);
		parse_map(game, lines);
		ft_free_2d_char(lines);
		close(fd);
	}
	else
	{
		ft_putstr_fd("bad format\n", 2);
		return (-1);
	}
	return (0);
}
