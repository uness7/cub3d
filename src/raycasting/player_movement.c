/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblot-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:42:11 by tblot-la          #+#    #+#             */
/*   Updated: 2024/10/03 11:42:23 by tblot-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_move(double new_x, double new_y, t_game *game)
{
	long	map_x;
	long	map_y;

	map_x = ((game->player.x + new_x) / TILESIZE);
	map_y = ((game->player.y + new_y) / TILESIZE);
	if (map_y < 0 || map_x < 0)
		return ;
	if (map_y >= game->map->max_y || map_x >= game->map->max_x)
		return ;
	if (game->map->map_cpy[map_y][map_x] == '0'
		|| game->map->map_cpy[map_y][map_x] == (char)game->player.orientation)
	{
		game->player.x += new_x;
		game->player.y += new_y;
	}
}

void	move_player(t_game *game, double new_x, double new_y)
{
	if (game->player.ws == 1)
	{
		new_x = cos(game->player.angle) * MOVESPEED;
		new_y = sin(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ws == -1)
	{
		new_x = -cos(game->player.angle) * MOVESPEED;
		new_y = -sin(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ad == 1)
	{
		new_x = -sin(game->player.angle) * MOVESPEED;
		new_y = cos(game->player.angle) * MOVESPEED;
	}
	else if (game->player.ad == -1)
	{
		new_x = sin(game->player.angle) * MOVESPEED;
		new_y = -cos(game->player.angle) * MOVESPEED;
	}
	check_move(new_x, new_y, game);
}

void	player_controller(t_game *game)
{
	if (game->player.rotate == 1)
	{
		game->player.angle += 0.001 * ROTSPEED;
	}
	else if (game->player.rotate == -1)
	{
		game->player.angle -= 0.001 * ROTSPEED;
	}
	if (game->player.ws != 0 || game->player.ad != 0)
	{
		move_player(game, 0, 0);
	}
	game->player.angle = angle_reset(game->player.angle);
}
