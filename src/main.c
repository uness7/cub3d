#include "../inc/cub3d.h"

void    allocate_memory_for_game(t_game **game)
{
    *game = malloc(sizeof(t_game));
    if (*game == NULL)
    {
        ft_putstr_fd("malloc failed\n", 2);
        exit(EXIT_FAILURE);
    }
    ft_memset(*game, 0, sizeof(t_game));
    (*game)->map = malloc(sizeof(t_map));
    if ((*game)->map == NULL)
    {
        ft_putstr_fd("malloc failed\n", 2);
        exit(EXIT_FAILURE);
    }
    ft_memset((*game)->map, 0, sizeof(t_map));
}

int	    main(int ac, char **av)
{
    t_game  *game;


    allocate_memory_for_game(&game);
	if (ac == 2)
    {
		parser(ac, av, game);
        init_max_x(game);
        init_max_y(game);
        init_x_row(game);
        init_window(game);
        //print_game_data(game);
    }
	else
		ft_putstr_fd("You need to add a map :(\n", 2);
	return (0);
}
