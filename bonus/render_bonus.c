/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:24:13 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:10:35 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to apply the lighting to the color according to the distance of the
wall */
static int	apply_lighting(int color, double lighting_factor)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	r = (int)(r * lighting_factor);
	g = (int)(g * lighting_factor);
	b = (int)(b * lighting_factor);
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return (get_rgba(r, g, b, a));
}

/* Function to get the color of the corresponding texture. It will return the
color of the texture according to the side of the wall and the direction of the
ray */
static int	get_color(t_data *data)
{
	uint8_t		*clr;
	uint32_t	color;
	double		lightning_factor;
	uint32_t	*pixels;

	if (data->ray.side == 1 && data->ray.ray_dir_y < 0)
		pixels = (uint32_t *)data->south_texture->pixels;
	else if (data->ray.side == 1 && data->ray.ray_dir_y > 0)
		pixels = (uint32_t *)data->north_texture->pixels;
	else if (data->ray.side == 0 && data->ray.ray_dir_x < 0)
		pixels = (uint32_t *)data->east_texture->pixels;
	else
		pixels = (uint32_t *)data->west_texture->pixels;
	if (data->map[data->ray.map_y][data->ray.map_x] == 'D')
		pixels = (uint32_t *)data->door_texture->pixels;
	else if (data->map[data->ray.map_y][data->ray.map_x] == 'X')
		pixels = (uint32_t *)data->enemy->pixels;
	clr = (uint8_t *)&pixels[64 * data->ray.tex_y + (64 - data->ray.tex_x - 1)];
	color = get_rgba(clr[0], clr[1], clr[2], 255);
	lightning_factor = 1.0 / (1.0 + data->ray.perp_wall_dist * 0.5);
	color = apply_lighting(color, lightning_factor);
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
		ft_draw_ray(data, data->palette[12]);
		kill_count(data);
		frames = 0;
	}
	data->renderer.changed = false;
}
