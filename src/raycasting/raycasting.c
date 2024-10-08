/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:42:36 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/03 11:42:38 by tblot-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	get_h_inter(t_game *game)
{
	double	h_x;
	double	h_y;
	double	x_step;
	double	y_step;
	int		pixel;

	y_step = TILESIZE;
	x_step = TILESIZE / tan(game->ray.angle);
	h_y = floor(game->player.y / TILESIZE) * TILESIZE;
	pixel = check_inter(game, &y_step, &h_y, HORIZONTAL);
	h_x = game->player.x + (h_y - game->player.y) / tan(game->ray.angle);
	if ((game->ray.angle > M_PI / 2 && game->ray.angle < (3 * M_PI) / 2)
		&& x_step > 0)
		x_step *= -1;
	else if ((game->ray.angle > (3 * M_PI) / 2 || game->ray.angle < M_PI / 2)
		&& x_step < 0)
		x_step *= -1;
	while (!check_hit(game, h_x, h_y - pixel))
	{
		h_x += x_step;
		h_y += y_step;
	}
	game->ray.x_h = h_x;
	game->ray.y_h = h_y;
	return (sqrt(pow(h_x - game->player.x, 2) + pow(h_y - game->player.y, 2)));
}

double	get_v_inter(t_game *game)
{
	double	v_x;
	double	v_y;
	double	x_step;
	double	y_step;
	int		pixel;

	x_step = TILESIZE;
	y_step = TILESIZE * tan(game->ray.angle);
	v_x = floor(game->player.x / TILESIZE) * TILESIZE;
	pixel = check_inter(game, &x_step, &v_x, VERTICAL);
	v_y = game->player.y + (v_x - game->player.x) * tan(game->ray.angle);
	if ((game->ray.angle > M_PI && game->ray.angle < 2 * M_PI) && y_step > 0)
		y_step *= -1;
	else if ((game->ray.angle < M_PI && game->ray.angle > 0) && y_step < 0)
		y_step *= -1;
	while (!check_hit(game, v_x - pixel, v_y))
	{
		v_x += x_step;
		v_y += y_step;
	}
	game->ray.x_v = v_x;
	game->ray.y_v = v_y;
	return (sqrt(pow(v_x - game->player.x, 2) + pow(v_y - game->player.y, 2)));
}

void	render_line(t_game *game, int ray)
{
	double	line_l;
	double	top_p;
	double	bottom_p;

	game->ray.distance *= cos(angle_reset(game->ray.angle
				- game->player.angle));
	line_l = (TILESIZE / game->ray.distance) * ((SCREEN_WIDTH / 2)
			/ tan(game->player.rd_fov / 2));
	bottom_p = (SCREEN_HEIGHT / 2) + (line_l / 2);
	top_p = (SCREEN_HEIGHT / 2) - (line_l / 2);
	game->ray.wall_l = line_l;
	if (bottom_p > SCREEN_HEIGHT)
		bottom_p = SCREEN_HEIGHT;
	if (top_p < 0)
		top_p = 0;
	put_line(top_p, bottom_p, ray, game);
}

void	castrays(t_game *game)
{
	int		ray;
	double	h_inter;
	double	v_inter;

	ray = 0;
	game->ray.angle = game->player.angle - (game->player.rd_fov / 2);
	while (ray < SCREEN_WIDTH)
	{
		game->ray.angle = angle_reset(game->ray.angle);
		h_inter = get_h_inter(game);
		v_inter = get_v_inter(game);
		if (v_inter <= h_inter)
		{
			game->ray.distance = v_inter;
			game->ray.type = VERTICAL;
		}
		else
		{
			game->ray.distance = h_inter;
			game->ray.type = HORIZONTAL;
		}
		render_line(game, ray);
		ray++;
		game->ray.angle += (game->player.rd_fov / SCREEN_WIDTH);
	}
}
