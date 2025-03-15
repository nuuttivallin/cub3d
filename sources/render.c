/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:09:03 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Function get the color of the corresponding texture. It will return 
the color of the texture according to the side of the wall and the 
direction of the ray */
static int	get_color(t_data *data)
{
	uint8_t		*clr;
	uint32_t	color;
	uint32_t	*pixels;

	if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		pixels = (uint32_t *)data->south_texture->pixels;
	else if (data->ray.side == 1 && data->ray.ray_dir_y > 0)
		pixels = (uint32_t *)data->north_texture->pixels;
	else if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
		pixels = (uint32_t *)data->east_texture->pixels;
	else
		pixels = (uint32_t *)data->west_texture->pixels;
	clr = (uint8_t *)&pixels[64 * data->ray.tex_y + (64 - data->ray.tex_x - 1)];
	color = get_rgba(clr[0], clr[1], clr[2], 255);
	return (color);
}

/* Function to calculate the image to be rendered, placing the corresponding
pixel color in the image */
static void	calculate_img(t_data *data)
{
	t_img		img;
	double		step;
	uint32_t	color;	

	img.x = -1;
	while (++img.x < WIDTH)
	{
		raycast(data, img.x);
		step = 1.0 * 64 / data->ray.line_height;
		data->ray.tex_pos = (data->ray.draw_start - HEIGHT / 2 + \
							data->ray.line_height / 2) * step;
		img.y = data->ray.draw_start - 1;
		while (++img.y < data->ray.draw_end)
		{
			data->ray.tex_y = (int)data->ray.tex_pos & 63;
			data->ray.tex_pos += step;
			color = get_color(data);
			mlx_put_pixel(data->img, img.x, img.y, color);
		}
	}
}

/* Function to render the image. It will only render if the frames are greater
than the frame wait */
void	render(void *param)
{
	static int	frames = 0;
	t_data		*data;

	data = (t_data *)param;
	if (data->renderer.changed || ++frames > FRAME_WAIT)
	{
		draw_ceiling_and_floor(data);
		calculate_img(data);
		frames = 0;
	}
	data->renderer.changed = false;
}
