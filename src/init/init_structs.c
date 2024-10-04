# include "../../inc/cub3d.h"

void    get_colors(t_game *game, char *rgb, char *space) 
{
    t_color colors;
    char	**split;

    if (rgb == NULL)
    {
        ft_putstr_fd("rgb array in get_colors is NULL\n", 2);
        exit(EXIT_FAILURE);
    }
    split = ft_split(rgb, ',');
    if (!split || !split[0] || !split[1] || !split[2] || !split[3])
    {
        ft_free_2d_char(split);
        ft_putstr_fd("Something wrong ft_split function\n", 2);
        exit(EXIT_FAILURE);
    }
    colors.r = ft_atoi(split[1]);
    colors.g = ft_atoi(split[2]);
    colors.b = ft_atoi(split[3]);
    colors.rgb = (colors.r << 16) + (colors.g << 8) + colors.b;
    ft_free_2d_char(split);
    init_colors(game, colors, space); 
}


void    init_colors(t_game *game, t_color colors, char *space)
{
    if (ft_strncmp(space, "floor", 6) == 0)
    {
        game->map->floor = colors;
    }
    else if (ft_strncmp(space, "ceiling", 8) == 0)
    {
        game->map->ceiling = colors;
    }
    else
    {
        ft_putstr_fd("Expected floor or ceiling !\n", 2);
        exit(EXIT_FAILURE);
    }
}

void    get_textures(t_game *game, char **textures)
{
    int         i;
    char    **split;

    i = -1;
    while (textures[++i] != NULL)
    {
        split = ft_split(textures[i], ' ');
        if (!split || !split[0] || !split[1])
        {
            ft_free_2d_char(split);
            ft_putstr_fd("Something is wrong with the textures\n", 2);
            exit(EXIT_FAILURE);
        }
        if (ft_strncmp(split[0], "NO", 2) == 0)
        {
            game->map->textures.north = ft_strdup(split[1]);
            if (game->map->textures.north == NULL)
            {
                perror("ft_strdup failed");
                ft_free_2d_char(split);
                exit(EXIT_FAILURE);
            }
        }

        if (ft_strncmp(split[0], "SO", 2) == 0)
        {
            game->map->textures.south = ft_strdup(split[1]);
            if (game->map->textures.south == NULL)
            {
                perror("ft_strdup failed");
                ft_free_2d_char(split);
                exit(EXIT_FAILURE);
            }
        }

        if (ft_strncmp(split[0], "EA", 2) == 0)
        {
            game->map->textures.east = ft_strdup(split[1]);
            if (game->map->textures.east == NULL)
            {
                perror("ft_strdup failed");
                ft_free_2d_char(split);
                exit(EXIT_FAILURE);
            }
        }

        if (ft_strncmp(split[0], "WE", 2) == 0)
        {
            game->map->textures.west = ft_strdup(split[1]);
            if (game->map->textures.west == NULL)
            {
                perror("ft_strdup failed");
                ft_free_2d_char(split);
                exit(EXIT_FAILURE);
            }
        }
        ft_free_2d_char(split);
    }
}

void    ft_malloc_err(void)
{
    ft_putstr_fd("malloc_failed", 2);
    exit(EXIT_FAILURE);
}

void    load_textures(t_game *game)
{
    if (game->map->textures.north != NULL)
    {
        game->map->textures.north_tx = mlx_load_png(game->map->textures.north);
        if (!game->map->textures.north_tx)
            ft_malloc_err();
    }
    else {
        printf("tried to load textures but failed\n");
    }

    if (game->map->textures.south != NULL)
    {
        game->map->textures.south_tx = mlx_load_png(game->map->textures.south);
        if (!game->map->textures.south_tx)
            ft_malloc_err();
    }
    else {
        printf("tried to load textures but failed\n");
    }

    if (game->map->textures.east != NULL)
    {
        game->map->textures.east_tx = mlx_load_png(game->map->textures.east);
        if (!game->map->textures.east_tx)
            ft_malloc_err();
    }
    else {
        printf("tried to load textures but failed\n");
    }


    if (game->map->textures.west != NULL)
    {
        game->map->textures.west_tx = mlx_load_png(game->map->textures.west);
        if (!game->map->textures.west_tx)
            ft_malloc_err();
    }
    else {
        printf("tried to load textures but failed\n");
    }
}


void	load_map(t_game *game, char **map, int num_lines)
{
    int        i;

    i = -1;
    while (++i < num_lines)
    {
        game->map->map_cpy[i] = ft_strdup(map[i]);
        if (game->map->map_cpy[i] == NULL)
            exit(EXIT_FAILURE);
    }
    game->map->map_cpy[i] = NULL;
}
