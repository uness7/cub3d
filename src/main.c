# include "cub3d.h"

#define TILESIZE 32
#define MAP_WIDTH 11
#define MAP_HEIGHT 10
#define WIN_WIDTH (TILESIZE * MAP_WIDTH)
#define WIN_HEIGHT (TILESIZE * MAP_HEIGHT)

typedef struct s_game
{
	void	*mlx;
	void	*window;
	int	player_x;
	int	player_y;
}	t_game;

int	map[MAP_WIDTH][MAP_HEIGHT] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 0, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void draw_square(t_game *game, int x, int y, int color)
{
    int start_x = x * TILESIZE;
    int start_y = y * TILESIZE;
    int i, j;

    for (i = 0; i < TILESIZE; i++)
    {
        for (j = 0; j < TILESIZE; j++)
        {
            mlx_pixel_put(game->mlx, game->window, start_x + j, start_y + i, color);
        }
    }
}

void render_map(t_game *game, const int map[MAP_WIDTH][MAP_HEIGHT])
{
    int x, y;

    for (y = 0; y < MAP_HEIGHT; y++)
    {
        for (x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x] == 1)
                draw_square(game, x, y, 0xFFFFFF); // Draw walls in white
            else
                draw_square(game, x, y, 0x000000); // Empty spaces in black
        }
    }

    // Draw the player
    draw_square(game, game->player_x, game->player_y, 0xFF0000); // Player in red
}


int	main(/*int ac, char **av*/)
{
	t_game	game;
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "Simple Map");

	game.player_x = 1;
	game.player_y = 1;
	render_map(&game, map);
	mlx_loop(game.mlx);

	return (0);
}
