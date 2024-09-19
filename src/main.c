# include "cub3d.h"

int	main(int ac, char **av)
{
	if (ac == 2) 
		parser(ac, av);
	else
		printf("You need to add a map :(\n");
	return (0);
}
