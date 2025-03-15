/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:14:56 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:22:32 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to load the door texture into the data struct */
int	ft_get_door_texture(t_data *data)
{
	data->door_texture = mlx_load_png("textures/eagle.png");
	if (!data->door_texture)
	{
		write(2, "Error\ninvalid door texture\n", 27);
		return (1);
	}
	return (0);
}

/* Function to check if the player is near a door, and if so, identifies whether
 it is a closed or open door */
static int	ft_is_near_door(t_data *data, char axis, int direction)
{
	double	y;
	double	x;

	y = data->player.pos_y;
	x = data->player.pos_x;
	if (axis == 'y')
	{
		if ((direction > 0 && data->map[(int)(y + 0.5)][(int)x] == 'D')
			|| (direction < 0 && data->map[(int)(y - 0.5)][(int)x] == 'D'))
			return (1);
		if ((direction > 0 && data->map[(int)(y + 0.5)][(int)x] == 'd')
			|| (direction < 0 && data->map[(int)(y - 0.5)][(int)x] == 'd'))
			return (2);
	}
	if (axis == 'x')
	{
		if ((direction > 0 && data->map[(int)y][(int)(x + 0.5)] == 'D')
			|| (direction < 0 && data->map[(int)y][(int)(x - 0.5)] == 'D'))
			return (1);
		if ((direction > 0 && data->map[(int)y][(int)(x + 0.5)] == 'd')
			|| (direction < 0 && data->map[(int)y][(int)(x - 0.5)] == 'd'))
			return (2);
	}
	return (0);
}

/* Function to check if the door can be placed in the given position */
static bool	valid_door_position(t_data *data, int x, int y)
{
	char	**map;
	int		y_p;
	int		y_n;

	map = data->map;
	y_p = ft_strlen(map[y + 1]) - 1;
	y_n = ft_strlen(map[y - 1]) - 1;
	if (x > 0 && x < (int)ft_strlen(map[y]) - 1 && \
		y > 0 && y < data->map_height - 1)
	{
		if (map[y][x - 1] == '1' && map[y][x + 1] == '1' && (x < y_n && \
			map[y - 1][x] == '0' && (x < y_p && map[y + 1][x] == '0')) && \
			(x - 1 < y_n && map[y - 1][x - 1] != '1' && x + 1 < y_n && \
			map[y - 1][x + 1] != '1') && (x - 1 < y_p && map[y + 1][x - 1] != \
			'1' && x + 1 < y_p && map[y + 1][x + 1] != '1'))
			return (true);
		if ((x < y_n && map[y - 1][x] == '1' && x < y_p && map[y + 1][x] == \
			'1') && (map[y][x - 1] == '0' && map[y][x + 1] == '0') && (x - 1 < \
			y_n && map[y - 1][x - 1] != '1' && x + 1 < y_n && map[y - 1][x + 1] \
			!= '1') && (x - 1 < y_p && map[y + 1][x - 1] != '1' && x + 1 < y_p \
			&& map[y + 1][x + 1] != '1'))
			return (true);
	}
	return (false);
}

/* Function to place the doors in the map */
void	place_doors(t_data *data)
{
	int	x;
	int	y;

	y = 1;
	while (y < data->map_height - 3)
	{
		x = 1;
		while (x < (int)ft_strlen(data->map[y]) - 3)
		{
			if (valid_door_position(data, x, y))
				data->map[y][x] = 'd';
			x++;
		}
		y++;
	}
}

/* Function to interact with the doors. If the player is near a door, it will
 open or close it, depending on its current state */
void	door_interaction(t_data *data)
{
	int			door_y;
	int			door_x;

	if (ft_is_near_door(data, 'y', 1) || ft_is_near_door(data, 'y', -1)
		|| ft_is_near_door(data, 'x', 1) || ft_is_near_door(data, 'x', -1))
	{
		door_y = (int)(data->player.pos_y + data->player.dir_y * 0.6);
		door_x = (int)(data->player.pos_x + data->player.dir_x * 0.6);
		if (data->map[door_y][door_x] == 'D')
		{
			data->map[door_y][door_x] = 'd';
			data->map_frame->instances[the_door(data)].enabled = false;
			mlx_set_instance_depth(&data->map_frame->instances[the_door(data)], \
			100);
		}
		else if (data->map[door_y][door_x] == 'd' && \
			data->map[(int)data->player.pos_y][(int)data->player.pos_x] != 'd')
		{
			data->map[door_y][door_x] = 'D';
			data->map_frame->instances[the_door(data)].enabled = true;
			mlx_set_instance_depth(&data->map_frame->instances[the_door(data)], \
			10);
		}
		data->renderer.changed = true;
	}
}
