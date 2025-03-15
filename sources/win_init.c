/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:08:12 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:20:32 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Function to initialize the color palette. It will create a gradient of colors
from black to white */
void	init_color_palette(t_data *data)
{
	double	t;
	int		i;
	int		r;
	int		g;
	int		b;

	i = 1;
	data->palette[0] = 0xAA;
	while (i < ITER)
	{
		t = (double)i / (ITER / 5);
		r = (int)(data->color.r_o * (1 - t) * t * t * t * 255);
		g = (int)(data->color.g_o * (1 - t) * (1 - t) * t * t * 255);
		b = (int)(data->color.b_o * (1 - t) * (1 - t) * (1 - t) * t * 255);
		data->palette[i] = (r << 24) | (g << 16) | (b << 8) | 255;
		i++;
	}
}

/* Function to initialize the layout of the window. It will set the zoom factor
to 1.0, the color of the palette to a greenish color and the frames to wait to
5 */
void	get_layout(t_data *data)
{
	data->color.r_o = 9;
	data->color.g_o = 15;
	data->color.b_o = 8.5;
	data->renderer.frames = FRAME_WAIT;
	data->renderer.changed = true;
}

/* Function to draw the ceiling and the floor. It will draw the ceiling and the
floor with the colors set in the data struct */
void	draw_ceiling_and_floor(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(data->img, x, y, data->ceiling_rgba);
	}
	y--;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(data->img, x, y, data->floor_rgba);
	}
}

/* Function to initialize the window. It will get the layout of the window, set
the color palette and initialize the mlx instance */
void	win_init(t_data *data)
{
	get_layout(data);
	init_color_palette(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		exit(EXIT_FAILURE);
	draw_ceiling_and_floor(data);
	return ;
}
