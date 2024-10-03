/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:43:10 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/03 11:43:11 by tblot-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int     check_inter(t_game *game, double *step, double *inter, t_orientation o)
{
    if (o == HORIZONTAL)
    {
        if (game->ray.angle > 0 && game->ray.angle < M_PI)
        {
            *inter += TILESIZE;
            return (-1);
        }
        *step *= -1;
    }
    else if (o == VERTICAL)
    {
        if (!(game->ray.angle > M_PI / 2 && game->ray.angle < 3 * M_PI /2))
        {
            *inter += TILESIZE;
            return (-1);
        }
        *step *= -1;
    }
    return (1);
}

double  angle_reset(double angle)
{
    if (angle > M_PI * 2)
        return (angle -= M_PI * 2);
    if (angle < 0)
        return (angle += M_PI * 2);
    else
        return (angle);
}

int	reverse_bytes(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}
