/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:29:33 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:07:35 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Function to initialize the ray. It will set the camera_x to the value of the
ray's map_x divided by the width of the window. It will set the ray direction
x and y to the player's direction x and y plus the player's plane x and y
multiplied by the camera_x. It will set the ray's map_x and map_y to the
player's position x and y. It will set the ray's delta distance x and y to the
absolute value of 1 divided by the ray's direction x and y. */
static void	init_ray(t_data *data, int x)
{
	ft_bzero(&data->ray, sizeof(t_ray));
	data->ray.map_x = (int)data->player.pos_x;
	data->ray.map_y = (int)data->player.pos_y;
	data->ray.camera_x = 2 * x / (double)WIDTH - 1;
	data->ray.ray_dir_x = data->player.dir_x + data->player.plane_x
		* data->ray.camera_x;
	data->ray.ray_dir_y = data->player.dir_y + data->player.plane_y
		* data->ray.camera_x;
	data->ray.delta_dist_x = fabs(1 / data->ray.ray_dir_x);
	data->ray.delta_dist_y = fabs(1 / data->ray.ray_dir_y);
}

/* Function to set the DDA. It will set the step x to -1 if the ray direction x
is less than 0, otherwise it will set it to 1. It will set the side distance x
to the player's position x minus the ray's map x multiplied by the ray's delta
distance x if the ray direction x is less than 0, otherwise it will set it to
the ray's map x plus 1 minus the player's position x multiplied by the ray's
delta distance x. It will set the step y to -1 if the ray direction y is less
than 0, otherwise it will set it to 1. It will set the side distance y to the
player's position y minus the ray's map y multiplied by the ray's delta
distance y if the ray direction y is less than 0, otherwise it will set it to
the ray's map y plus 1 minus the player's position y multiplied by the ray's
delta distance y. */
static void	set_dda(t_data *data)
{
	if (data->ray.ray_dir_x < 0)
	{
		data->ray.step_x = -1;
		data->ray.side_dist_x = (data->player.pos_x - data->ray.map_x)
			* data->ray.delta_dist_x;
	}
	else
	{
		data->ray.step_x = 1;
		data->ray.side_dist_x = (data->ray.map_x + 1.0 - data->player.pos_x)
			* data->ray.delta_dist_x;
	}
	if (data->ray.ray_dir_y < 0)
	{
		data->ray.step_y = -1;
		data->ray.side_dist_y = (data->player.pos_y - data->ray.map_y)
			* data->ray.delta_dist_y;
	}
	else
	{
		data->ray.step_y = 1;
		data->ray.side_dist_y = (data->ray.map_y + 1.0 - data->player.pos_y)
			* data->ray.delta_dist_y;
	}
}

/* Function to perform the DDA. It will loop until it finds a wall. It will
increment the side distance x by the delta distance x if the side distance x is
less than the side distance y. It will increment the map x by the step x and
set the side to 0. It will increment the side distance y by the delta distance y
if the side distance y is less than the side distance x. It will increment the
map y by the step y and set the side to 1. If the map at the ray's map y and x
is equal to 1, it will break the loop. */
static void	perform_dda(t_data *data)
{
	while (1)
	{
		if (data->ray.side_dist_x < data->ray.side_dist_y)
		{
			data->ray.side_dist_x += data->ray.delta_dist_x;
			data->ray.map_x += data->ray.step_x;
			data->ray.side = 0;
		}
		else
		{
			data->ray.side_dist_y += data->ray.delta_dist_y;
			data->ray.map_y += data->ray.step_y;
			data->ray.side = 1;
		}
		if (data->ray.map_y < 0 || data->ray.map_x < 0
			|| data->ray.map_y >= data->map_height
			|| data->ray.map_x >= (int)ft_strlen(data->map[data->ray.map_y]))
			break ;
		if (data->map[data->ray.map_y][data->ray.map_x] == '1'
			|| data->map[data->ray.map_y][data->ray.map_x] == 'D')
			break ;
	}
}

/* Function to calculate the wall. It will set the perpendicular wall distance
to the ray's map x minus the player's position x plus 1 minus the ray's step x
divided by 2 divided by the ray's direction x if the ray's side is 0, otherwise
it will set it to the ray's map y minus the player's position y plus 1 minus
the ray's step y divided by 2 divided by the ray's direction y. It will set the
line height to the integer value of the height divided by the perpendicular
wall distance. It will set the draw start to the negative value of the line
height divided by 2 plus the height divided by 2. If the draw start is less
than 0, it will set it to 0. It will set the draw end to the line height
divided by 2 plus the height divided by 2. If the draw end is greater than or
equal to the height, it will set it to the height minus 1. If the ray's side is
0, it will set the wall x to the player's position y plus the perpendicular
wall distance multiplied by the ray's direction y, otherwise it will set it to
the player's position x plus the perpendicular wall distance multiplied by the
ray's direction x. It will subtract the floor of the wall x from the wall x. */
static void	calc_wall(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.perp_wall_dist = data->ray.side_dist_x - \
									data->ray.delta_dist_x;
	else
		data->ray.perp_wall_dist = data->ray.side_dist_y - \
									data->ray.delta_dist_y;
	data->ray.line_height = (int)(HEIGHT / data->ray.perp_wall_dist);
	data->ray.draw_start = -data->ray.line_height / 2 + HEIGHT / 2;
	if (data->ray.draw_start < 0)
		data->ray.draw_start = 0;
	data->ray.draw_end = data->ray.line_height / 2 + HEIGHT / 2;
	if (data->ray.draw_end >= HEIGHT)
		data->ray.draw_end = HEIGHT - 1;
	if (data->ray.side == 0)
		data->ray.wall_x = data->player.pos_y + data->ray.perp_wall_dist
			* data->ray.ray_dir_y;
	else
		data->ray.wall_x = data->player.pos_x + data->ray.perp_wall_dist
			* data->ray.ray_dir_x;
	data->ray.wall_x -= floor(data->ray.wall_x);
	data->ray.tex_x = (int)(data->ray.wall_x * (double)64);
	if (data->ray.side == 0 && data->ray.ray_dir_x > 0)
		data->ray.tex_x = 64 - data->ray.tex_x - 1;
	if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		data->ray.tex_x = 64 - data->ray.tex_x - 1;
}

/* Function to execute the raycasting. It will initialize the ray, set the DDA,
perform the DDA and calculate the wall. */
void	raycast(t_data *data, int x)
{
	init_ray(data, x);
	set_dda(data);
	perform_dda(data);
	calc_wall(data);
}
