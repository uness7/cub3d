#include "../inc/cub3d.h"

int	main(int ac, char **av)
{
	if (ac == 2)
		parser(ac, av);
	else
		ft_putstr_fd("You need to add a map :(\n", 2);
	return (0);
}
