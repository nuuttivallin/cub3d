/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:46:56 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:10:13 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to calculate the y position of the ray */
static int	ft_y_ray(double direction, double *y_draw)
{
	static double	y_step = 0;

	y_step += direction;
	*y_draw += direction;
	if (direction > 0 && y_step > 8)
	{
		y_step = -8;
		return (1);
	}
	else if (direction < 0 && y_step < -8)
	{
		y_step = 8;
		return (-1);
	}
	return (0);
}

/* Function to calculate the x position of the ray */
static int	ft_x_ray(double direction, double *x_draw)
{
	static double	x_step = 0;

	x_step += direction;
	*x_draw += direction;
	if (direction > 0 && x_step > 8)
	{
		x_step = -8;
		return (1);
	}
	else if (direction < 0 && x_step < -8)
	{
		x_step = 8;
		return (-1);
	}
	return (0);
}

/* Function to draw the rays on the minimap */
void	ft_draw_ray(t_data *data, int color)
{
	double	x;
	double	y;
	double	x_draw;
	double	y_draw;
	double	angle;

	angle = data->player.angle - (FOV / 2);
	while (angle < data->player.angle + (FOV / 2))
	{
		x_draw = 258;
		y_draw = 258;
		x = data->player.pos_x;
		y = data->player.pos_y;
		while ((int)y > 0 && (int)y < data->map_height - 1 && (int)x > 0 && \
			(int)x < (int)ft_strlen(data->map[(int)y]) - 1 && \
			data->map[(int)y][(int)x] != '1' && \
			data->map[(int)y][(int)x] != 'D')
		{
			if (sqrt(pow((258 - x_draw), 2) + pow((258 - y_draw), 2)) < 64)
				mlx_put_pixel(data->img, x_draw, y_draw, color);
			y += ft_y_ray(sin(angle), &y_draw);
			x += ft_x_ray(cos(angle), &x_draw);
		}
		angle += 0.001;
	}
}
