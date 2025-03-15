/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:54:53 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:28:02 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to calculate the rotation of the player. If the direction is 'l',
the player rotates to the left, and if the direction is 'r', the player rotates
to the right. Then calculates the new direction of the player. */
void	ft_rotate_player(t_data *data, char direction)
{
	if (direction == 'l')
	{
		data->player.angle -= PI / 90 * 2;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
		data->player.plane_x = -sin(data->player.angle) * 0.66;
		data->player.plane_y = cos(data->player.angle) * 0.66;
	}
	if (direction == 'r')
	{
		data->player.angle += PI / 90 * 2;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
		data->player.plane_x = -sin(data->player.angle) * 0.66;
		data->player.plane_y = cos(data->player.angle) * 0.66;
	}
	data->renderer.changed = true;
}

/* Function to check if the player is near a wall. If the player is near a wall,
a door or an enemy, the function returns 1, otherwise it returns 0. */
static int	ft_is_player_near_wall(t_data *data, char axis, int direction)
{
	double	y;
	double	x;
	char	c;

	y = data->player.pos_y;
	x = data->player.pos_x;
	if (axis == 'y')
	{
		if (direction > 0)
			c = data->map[(int)(y + 0.375)][(int)x];
		else
			c = data->map[(int)(y - 0.375)][(int)x];
	}
	if (axis == 'x')
	{
		if (direction > 0)
			c = data->map[(int)y][(int)(x + 0.375)];
		else
			c = data->map[(int)y][(int)(x - 0.375)];
	}
	if (c == '1' || c == 'D' || c == 'X')
		return (1);
	return (0);
}

/* Function to move the player in the y direction. If the direction is negative
and the player is not near a wall, the player moves in the negative y direction.
If the direction is positive and the player is not near a wall, the player moves
in the positive y direction. */
void	ft_move_player_y(t_data *data, double direction)
{
	static double	pixels = 0;

	if (direction < 0 && !ft_is_player_near_wall(data, 'y', -1))
	{
		data->player.pos_y += direction / 20.0 * 2;
		pixels += direction / 1.25 * 2;
		if (pixels <= -2)
		{
			ft_move_minimap_y(data, direction);
			pixels += 2;
		}
	}
	else if (direction > 0 && !ft_is_player_near_wall(data, 'y', 1))
	{
		data->player.pos_y += direction / 20.0 * 2;
		pixels += direction / 1.25 * 2;
		if (pixels >= 2)
		{
			ft_move_minimap_y(data, direction);
			pixels -= 2;
		}
	}
}

/* Function to move the player in the x direction. If the direction is negative
and the player is not near a wall, the player moves in the negative x direction.
If the direction is positive and the player is not near a wall, the player moves
in the positive x direction. */
void	ft_move_player_x(t_data *data, double direction)
{
	static double	pixels = 0;

	if (direction < 0 && !ft_is_player_near_wall(data, 'x', -1))
	{
		data->player.pos_x += direction / 20.0 * 2;
		pixels += direction / 1.25 * 2;
		if (pixels <= -2)
		{
			ft_move_minimap_x(data, direction);
			pixels += 2;
		}
	}
	else if (direction > 0 && !ft_is_player_near_wall(data, 'x', 1))
	{
		data->player.pos_x += direction / 20.0 * 2;
		pixels += direction / 1.25 * 2;
		if (pixels >= 2)
		{
			ft_move_minimap_x(data, direction);
			pixels -= 2;
		}
	}
}

/* Function to move the player in the y and x direction. */
void	ft_move_player(t_data *data, double dir_y, double dir_x)
{
	ft_move_player_y(data, dir_y);
	ft_move_player_x(data, dir_x);
	data->renderer.changed = true;
}
