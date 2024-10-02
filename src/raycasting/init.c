# include "../../inc/cub3d.h"
#include <stdio.h>

void    terminate_game(void *game)
{
    (void)game;
    exit(1);
}

void    keyrelease(mlx_key_data_t keydata, t_game *game)
{
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
        game->player.ws = 0;
    else if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
        game->player.ws = 0;
    else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
        game->player.ad = 0;
    else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
        game->player.ad = 0;
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
        game->player.rotate = 0;
    else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
        game->player.rotate = 0;
}

void    keypress(mlx_key_data_t keydata, void *gameptr)
{
    t_game	*game;

    game = (t_game *)gameptr;
    if (keydata.key == MLX_KEY_ESCAPE)
        terminate_game(game);
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
        game->player.ws = 1;
    else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
        game->player.ws = -1;
    else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
        game->player.ad = 1;
    else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
        game->player.ad = -1;
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
        game->player.rotate = 1;
    else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
        game->player.rotate = -1;
    keyrelease(keydata, game);
}

void    game_loop(void *gameptr)
{
    t_game  *game;

    game = (t_game *)gameptr;
    castrays(game);
    player_controller(game);
}

void    init_window(t_game *game)
{
    game->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d", false);
    if (game->mlx == false)
        exit(1);

    game->pixel = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (game->pixel == false)
        exit(1);

    if (mlx_image_to_window(game->mlx, game->pixel, 0, 0) < 0)
        exit(0);

    init_player(game);
    mlx_loop_hook(game->mlx, &game_loop, game);
    mlx_key_hook(game->mlx, &keypress, game);
    mlx_close_hook(game->mlx, &terminate_game, game);
    mlx_loop(game->mlx);
}
