/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:42:47 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/03 11:42:48 by tblot-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void    init_x_row(t_game *game)
{
    int     i;
    int     j;

    game->map->x_row = malloc(sizeof(int) * (game->map->max_y + 1));
    if (game->map->x_row == NULL)
    {
        ft_putstr_fd("malloc failed", 2);
        exit(EXIT_FAILURE);
    }
    i = 0;
    j = 0;
    while (game->map->map_cpy[i] != NULL)
    {
        game->map->x_row[j] = ft_strlen(game->map->map_cpy[i]);
        i++;
        j++;
    }
}

void    init_max_y(t_game *game)
{
    int     i;

    i = 0;
    while (game->map->map_cpy[i] != NULL)
        i++;
    game->map->max_y = i;
}

void    init_max_x(t_game *game)
{
    int     i;
    int     len;

    i = 0;
    len = 0;
    game->map->max_x = 0;
    while (game->map->map_cpy[i] != NULL)
    {
        len = ft_strlen(game->map->map_cpy[i]);
        if ((unsigned int)len > game->map->max_x)
            game->map->max_x = len;
        i++;
    }
}

bool    check_hit(t_game *game, double x, double y)
{
    unsigned int    x_m;
    unsigned int    y_m;

    if (x < 0 || y < 0)
        return true;
    x_m = (unsigned int)floor(x / TILESIZE);
    y_m = (unsigned int)floor(y / TILESIZE);
    if ((y_m >= game->map->max_y || x_m >= game->map->x_row[y_m]))
        return (true);
    if (game->map->map_cpy[(int)y_m])
    {
        if (game->map->map_cpy[(int)y_m][(int)x_m])
        {
            if (game->map->map_cpy[(int)y_m][(int)x_m] == '1')
                return (true);
        }
    }
    return (false);
}
