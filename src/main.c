# include <stdio.h>
# include <stdlib.h>
# include "parser.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	printf("Hello world!\n");
	parse_file();
	printf("\n");
	return 0;
}
