/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:26:48 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:10:17 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to draw the minimap frame */
int	ft_draw_minimap_frame(t_data *data)
{
	int	i;

	i = 100;
	while (i < 420)
	{
		if (mlx_image_to_window(data->mlx, data->map_frame, i, 100) == -1 || \
			mlx_image_to_window(data->mlx, data->map_frame, 100, i) == -1)
		{
			perror("minimap frame");
			return (1);
		}
		i += 16;
	}
	while (i >= 100)
	{
		if (mlx_image_to_window(data->mlx, data->map_frame, i, 420) == -1 || \
			mlx_image_to_window(data->mlx, data->map_frame, 420, i) == -1)
		{
			perror("minimap frame");
			return (1);
		}
		i -= 16;
	}
	return (0);
}

/* Function to draw the player on the minimap */
int	ft_draw_player_to_minimap(t_data *data)
{
	int	i;

	i = 0;
	while (i < 82)
		mlx_set_instance_depth(&data->map_frame->instances[i++], 100);
	while (i < (int)data->map_frame->count)
		mlx_set_instance_depth(&data->map_frame->instances[i++], 10);
	i = 0;
	while (i < (int)data->map_wall->count)
		mlx_set_instance_depth(&data->map_wall->instances[i++], 10);
	if (!data->player.mini_p)
		data->player.mini_p = mlx_load_png("./textures/player1.png");
	if (!data->player.mini_p)
		return (1);
	data->player.mini_player = \
	mlx_texture_to_image(data->mlx, data->player.mini_p);
	if (!data->player.mini_player || \
		!mlx_resize_image(data->player.mini_player, 16, 16) || \
		mlx_image_to_window(data->mlx, data->player.mini_player, \
		250, 250) == -1)
		return (1);
	ft_draw_ray(data, data->palette[12]);
	ft_move_minimap_y(data, 1);
	ft_move_minimap_y(data, -1);
	return (0);
}

/* Function to draw the minimap in the game window */
int	draw_minimap(t_data *d, int x, int y)
{
	int	m_x;
	int	m_y;

	m_y = d->player_pos[0] + ((y - 250) / 16);
	m_x = d->player_pos[1] + ((x - 250) / 16);
	if (!ft_is_player(d->map[m_y][m_x]) && d->map[m_y][m_x] != '1' && \
		d->map[m_y][m_x] != 'D' && d->map[m_y][m_x] != 'd')
		d->map[m_y][m_x] = '0';
	else if (d->map[m_y][m_x] == '1' && \
			mlx_image_to_window(d->mlx, d->map_wall, x, y) == -1)
		return (1);
	if (d->map[m_y][m_x] == '1')
		return (0);
	if (d->map[m_y][m_x] == 'd' && \
		mlx_image_to_window(d->mlx, d->map_frame, x, y) == -1)
		return (1);
	if (d->map[m_y][m_x] == 'd')
		d->map[m_y][m_x] = 'D';
	if ((!is_filled(d->map[m_y + 1][m_x], '0') && draw_minimap(d, x, y + 16)) \
		|| (!is_filled(d->map[m_y - 1][m_x], '0') && \
		draw_minimap(d, x, y - 16)) || (!is_filled(d->map[m_y][m_x + 1], '0') \
		&& draw_minimap(d, x + 16, y)) || \
		(!is_filled(d->map[m_y][m_x - 1], '0') && draw_minimap(d, x - 16, y)))
		return (1);
	return (0);
}

/* Function to change the minimap when moving in the y direction */
void	ft_move_minimap_y(t_data *data, double direction)
{
	int	i;

	i = 0;
	ft_move_minidoors_y(data, direction);
	while (i < (int)data->map_wall->count)
	{
		if (direction > 0)
			data->map_wall->instances[i].y -= 2;
		else
			data->map_wall->instances[i].y += 2;
		if (data->map_wall->instances[i].y > 100 && \
			data->map_wall->instances[i].y < 420 && \
			data->map_wall->instances[i].x > 100 && \
			data->map_wall->instances[i].x < 420)
			data->map_wall->instances[i].enabled = true;
		else
			data->map_wall->instances[i].enabled = false;
		i++;
	}
}

/* Function to change the minimap when moving in the x direction */
void	ft_move_minimap_x(t_data *data, double direction)
{
	int	i;

	i = 0;
	ft_move_minidoors_x(data, direction);
	while (i < (int)data->map_wall->count)
	{
		if (direction > 0)
			data->map_wall->instances[i].x -= 2;
		else
			data->map_wall->instances[i].x += 2;
		if (data->map_wall->instances[i].y > 100 && \
			data->map_wall->instances[i].y < 420 && \
			data->map_wall->instances[i].x > 100 && \
			data->map_wall->instances[i].x < 420)
			data->map_wall->instances[i].enabled = true;
		else
			data->map_wall->instances[i].enabled = false;
		i++;
	}
}
