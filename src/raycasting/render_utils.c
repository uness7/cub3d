/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:42:58 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/12 11:38:54 by yzioual          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_floor_sky(t_game *game, int ray, int top_p, int bottom_p)
{
	int	f_color;
	int	s_color;
	int	i;

	f_color = game->map->floor.rgb;
	s_color = game->map->ceiling.rgb;
	i = 0;
	while (bottom_p < SCREEN_HEIGHT)
	{
		mlx_put_pixel(game->pixel, ray, bottom_p, f_color);
		bottom_p++;
	}
	while (i < top_p)
	{
		mlx_put_pixel(game->pixel, ray, i, s_color);
		i++;
	}
}

mlx_texture_t	*get_ray_texture(t_game *game)
{
	mlx_texture_t	*texture;

	texture = NULL;
	if (game->ray.angle > M_PI && game->ray.angle < 2 * M_PI
		&& game->ray.type == HORIZONTAL)
		texture = game->map->textures.north_tx;
	else if (game->ray.angle < M_PI && game->ray.angle > 0
		&& game->ray.type == HORIZONTAL)
		texture = game->map->textures.south_tx;
	else if (game->ray.angle < 3 * M_PI / 2 && game->ray.angle > M_PI / 2
		&& game->ray.type == VERTICAL)
		texture = game->map->textures.west_tx;
	else if ((game->ray.angle > 3 * M_PI / 2 || game->ray.angle < M_PI / 2)
		&& game->ray.type == VERTICAL)
		texture = game->map->textures.east_tx;
	return (texture);
}

double	get_x_o(t_game *game, int t_width)
{
	double	x_o;

	if (game->ray.type == HORIZONTAL)
		x_o = (int)fmodf((game->ray.x_h * (t_width / TILESIZE)), t_width);
	else
		x_o = (int)fmodf((game->ray.y_v * (t_width / TILESIZE)), t_width);
	return (x_o);
}

void	put_line(int top_p, int bottom_p, int ray, t_game *game)
{
	double			y_o;
	double			x_o;
	double			step;
	mlx_texture_t	*texture;
	uint32_t		*pixels;

	texture = get_ray_texture(game);
	pixels = (uint32_t *)texture->pixels;
	step = (double)texture->width / game->ray.wall_l;
	x_o = get_x_o(game, texture->width);
	y_o = (top_p - (SCREEN_HEIGHT / 2) + (game->ray.wall_l / 2)) * step;
	if (y_o < 0)
		y_o = 0;
	put_floor_sky(game, ray, top_p, bottom_p);
	while (top_p < bottom_p)
	{
		mlx_put_pixel(game->pixel, ray, top_p, reverse_bytes(pixels[(int)y_o
				* texture->width + (int)x_o]));
		y_o += step;
		top_p++;
	}
}
