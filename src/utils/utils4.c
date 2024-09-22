# include "../../inc/cub3d.h"
#include <stdbool.h>
#include <stdio.h>

bool	check_first_nd_last_char(char **map, int rows)
{
    int     i;
    int     j;
    int     len;
    int     last;

    i = -1;
    j = 0;
    while (++i < rows)
    {
        j = 0;
        len = ft_strlen(map[i]);
        while (map[i][j] == ' ')
            j++;
        if (map[i][j] != '1')
        {
            ft_putstr_fd("Failed rule 2\n", 2);
            return (false);
        }
        last = len - 1;
        while (last >= 0 && (map[i][last] == ' ' || map[i][last] == '\n'))
            last--;
        if (map[i][last] != '1')
        {
            ft_putstr_fd("Failed rule 2\n", 2);
            return (false);
        }
    }
    return (true);
}

bool    check_adjacent_to_spaces(char **map, int rows)
{
    int i, j, len;

    for (i = 0; i < rows; i++)
    {
        len = ft_strlen(map[i]);
        for (j = 1; j < len - 1; j++)
        {
            if (map[i][j] == ' ') 
            {
                if (map[i][j - 1] != '1' && map[i][j - 1] != ' ')
                {
                    ft_putstr_fd("Failed rule 4\n", 2);
                    return false;
                }
                if (map[i][j + 1] != '1' && map[i][j + 1] != ' ')
                {
                    ft_putstr_fd("Failed rule 4\n", 2);
                    return false;
                }
            }
        }
    }
    return (true);
}

bool    check_row_longer_than_top(char **map, int rows)
{
    int i, j, len_curr, len_top;

    for (i = 1; i < rows; i++)
    {
        len_curr = ft_strlen(map[i]);
        len_top = ft_strlen(map[i - 1]);
        if (map[i][len_curr - 1] == '\n') // Ignore newline if present
            len_curr--;
        if (map[i - 1][len_top - 1] == '\n') // Ignore newline in top row if present
            len_top--;
        if (len_curr > len_top)
        {
            for (j = len_top; j < len_curr; j++)
            {
                if (map[i][j] != '1' && map[i][j] != ' ')
                {
                    printf("char : %c\ti = %d\tj = %d\n", map[i][j], i, j);
                    ft_putstr_fd("Failed rule 5\n", 2);
                    return (false);
                }
            }
        }
    }
    return (true);
}

bool    check_row_longer_than_bottom(char **map, int rows)
{
    int i, j, len_curr, len_bottom;

    for (i = 0; i < rows - 1; i++)
    {
        len_curr = ft_strlen(map[i]);
        len_bottom = ft_strlen(map[i + 1]);
        if (map[i][len_curr - 1] == '\n')  // Ignore newline if present
            len_curr--;
        if (map[i + 1][len_bottom - 1] == '\n')  // Ignore newline in bottom row if present
            len_bottom--;
        if (len_curr > len_bottom)
        {
            for (j = len_bottom; j < len_curr; j++)
            {
                if (map[i][j] != '1' && map[i][j] != ' ')
                {
                    ft_putstr_fd("Failed rule 6\n", 2);
                    return (false);
                }
            }
        }
    }
    return (true);
}

bool	is_map_valid(char **map, int num_lines)
{
	return (is_composed_of_valid_chars(map)\
            && has_multi_valid_chars(map, num_lines)\
            && check_first_nd_last_rows(map, num_lines)\
            && check_first_nd_last_char(map, num_lines)\
            && check_adjacent_to_spaces(map, num_lines)\
            && check_row_longer_than_top(map, num_lines)\
            && check_row_longer_than_bottom(map, num_lines));	
}
