/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:54:53 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:29:31 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Function to calculate the rotation of the player. If the direction is 'l',
the player rotates to the left, and if the direction is 'r', the player rotates
to the right. Then calculates the new direction of the player. */
void	ft_rotate_player(t_data *data, char direction)
{
	if (direction == 'l')
	{
		data->player.angle -= PI / 90;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
		data->player.plane_x = -sin(data->player.angle) * 0.66;
		data->player.plane_y = cos(data->player.angle) * 0.66;
	}
	if (direction == 'r')
	{
		data->player.angle += PI / 90;
		if (data->player.angle > 2 * PI)
			data->player.angle -= 2 * PI;
		data->player.dir_x = cos(data->player.angle);
		data->player.dir_y = sin(data->player.angle);
		data->player.plane_x = -sin(data->player.angle) * 0.66;
		data->player.plane_y = cos(data->player.angle) * 0.66;
	}
	data->player.moved = true;
}

/* Function to move the player in the y direction. If the direction is negative
and the player is not near a wall, the player moves in the negative y direction.
If the direction is positive and the player is not near a wall, the player moves
in the positive y direction. */
void	ft_move_player(t_data *data, double dir_y, double dir_x)
{
	if (dir_y < 0)
		data->player.pos_y += dir_y / 20.0;
	else if (dir_y > 0)
		data->player.pos_y += dir_y / 20.0;
	if (dir_x < 0)
		data->player.pos_x += dir_x / 20.0;
	else if (dir_x > 0)
		data->player.pos_x += dir_x / 20.0;
	data->player.moved = true;
	data->renderer.changed = true;
}
