#include "cub3d.h"

static void	copy_color(char **dest, char *line)
{
	*dest = ft_strdup(line);
	if (*dest == NULL)
	{
		ft_putstr_fd("Error: ft_strdup failed. \n", 2);
		free(dest);
		exit(EXIT_FAILURE);
	}
}

static bool	is_color(char *color)
{
	return (ft_strncmp(color, "F", 1) == 0 || ft_strncmp(color, "C", 1) == 0);
}

static char	**copy_colors(char **cpy_lines)
{
	char	**colors;
	int		i;
	int		j;

	i = -1;
	j = 0;
	colors = malloc(sizeof(char *) * NUM_OF_RGB_VALUES);
	if (colors == NULL)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(EXIT_FAILURE);
	}
	while (cpy_lines[++i] != NULL)
	{
		if (is_color(cpy_lines[i]) == true)
		{
			copy_color(&colors[j], cpy_lines[i]);
			j++;
		}
	}
	colors[j] = NULL;
	return (colors);
}

void	validate_colors(t_game *game, char **cpy_lines)
{
	char	**colors;

	colors = copy_colors(cpy_lines);
	if (ft_size_2d_arr((void **)colors) == 2 \
			&& is_valid_colors(colors) \
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
