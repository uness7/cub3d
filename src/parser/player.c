# include "../../inc/cub3d.h"

double  get_player_angle(t_game *game)
{
    if (game->player.orientation == NORTH)
        return (3 * M_PI / 2);
    else if (game->player.orientation == SOUTH)
        return (M_PI / 2);
    else if (game->player.orientation == WEST)
        return (M_PI);
    else if (game->player.orientation == EAST)
        return (0);
    return (0);
}

void    init_player(t_game *game)
{
    game->player.angle = get_player_angle(game);
    game->player.x = game->player.x * TILESIZE + TILESIZE / 2;
    game->player.y = game->player.y * TILESIZE + TILESIZE / 2;
    game->player.rd_fov = (FOV * M_PI) / 180;
    game->player.ws = 0;
    game->player.ad = 0;
}

void    find_player(t_game *game, char **map)
{
    int     i;
    int     j;
    int     len;

    i = 0;
    while (map[i] != NULL)
    {
        j = 0;
        len = ft_strlen(map[i]);
        while (j < len - 1)
        {
            if (map[i][j] == NORTH || map[i][j] == SOUTH || \
                    map[i][j] == EAST || map[i][j] == WEST)
            {
                game->player.orientation = map[i][j];
                game->player.x = i;
                game->player.y = j;
                //printf("player.x = %f\n", game->player.x);
            }
            j++;
        }
        i++;
    }
}
