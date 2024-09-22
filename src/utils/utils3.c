# include "../../inc/cub3d.h"
# include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
# include <string.h>

// IsFull = True;

// Rule 1 : the map should only be composed of {0, 1, N, S, E, W}
bool	is_composed_of_valid_chars(char **map)
{
    int		i;
    int		j;

    i = 0;
    while (map[i] != NULL)
    {
        j = 0;
        while (map[i][j] != '\0')
        {
            if (map[i][j] != '0' && map[i][j] != '1' \
                    && map[i][j] != 'N' && map[i][j] != 'S' \
                    && map[i][j] != 'W' && map[i][j] != 'E' \
                    && map[i][j] != ' '
                    && map[i][j] != '\n')
                return (false);
            j++;
        }
        i++;
    }
    return (true);
}

// Rule 2 : 
bool 	check_first_nd_last_rows(char **map, int rows)
{
    int         i;
    int         j;
    int         len;

    j = 0;
    i = -1;
    while (++i < rows)
    {
        j = 0;
        len = ft_strlen(map[i]);
        while (j < len && ft_isspace(map[i][j]))
            j++;        
        if (i == 0 || i == rows - 1)
        {
            while (j <= len - 1)
            {
                if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\n')
                {
                    printf("Map failed rule 2\n");
                    return (false);
                }
                j++;
            }
        }
    }
	return (true);
}

/* Helper Function */
static bool is_char_repeated(char **map, int rows)
{
    int         i;
    int         j;
    int         len;
    int         counter;

    j = 0;
    i = -1;
    counter = 0;
    while (++i < rows)
    {
        j = 0;
        len = strlen(map[i]);
        while (j <= len - 1)
        {
            if (map[i][j] == 'S' || map[i][j] == 'N'\
                    || map[i][j] == 'E' || map[i][j] == 'W')
                counter++; 
            j++;
        }
    }
    if (counter == 0 || counter != 1)
    {
        printf("counter = %d\n", counter);
        return (false);
    }
	return (true);
}

// Rule 3:
bool    has_multi_valid_chars(char **map, int rows)
{
    if (!is_char_repeated(map, rows))
    {
        ft_putstr_fd("Map has multi or zero valid chars\n", 2);
        return (false);
    }
    return (true);
}
