/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:51:02 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:08:09 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to update the gun frame. The gun is drawn in the center of the
screen and the frame is updated every time the player shoots. */
static int	update_frame(t_data *data, int frame, mlx_texture_t **gun)
{
	int	x_offset;

	x_offset = 0;
	if (frame == 1)
		x_offset = -60;
	data->gun[frame] = mlx_texture_to_image(data->mlx, *gun);
	if (!data->gun[frame])
	{
		print_error("Error converting gun texture to image");
		mlx_delete_texture(*gun);
		return (1);
	}
	mlx_resize_image(data->gun[frame], (*gun)->width * 6, (*gun)->height * 6);
	if (mlx_image_to_window(data->mlx, data->gun[frame],
			WIDTH / 2 - data->gun[frame]->width / 2 + x_offset,
			HEIGHT - data->gun[frame]->height) == -1)
	{
		print_error("Error drawing gun frame");
		mlx_delete_texture(*gun);
		return (1);
	}
	if (frame >= 1)
		data->gun[frame]->enabled = false;
	mlx_delete_texture(*gun);
	return (0);
}

/* Function to load the gun frames into the data struct */
int	load_frames(t_data *data)
{
	int				i;
	char			*filename;
	mlx_texture_t	*gun;

	filename = ft_strdup("textures/gun/frame_0.png");
	if (!filename)
	{
		print_error("Error allocating memory for gun filename");
		return (1);
	}
	i = -1;
	while (i++ < 4)
	{
		filename[19] = i + '0';
		gun = mlx_load_png(filename);
		if (!gun)
		{
			print_error("Error loading gun PNG");
			return (1);
		}
		if (update_frame(data, i, &gun))
			return (1);
	}
	free(filename);
	return (0);
}

/* Function to animate the gun when the space bar or left mouse button is
pressed. The gun is drawn in the center of the screen and the frame is updated
every time the player shoots. */
void	ft_shoot(void *param)
{
	static int	frame = 0;
	static bool	shooting = false;
	t_data		*data;

	data = (t_data *)param;
	if ((mlx_is_key_down(data->mlx, MLX_KEY_SPACE) || \
		mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT)) && !shooting)
	{
		shooting = true;
		enemies_interaction(data);
	}
	if (shooting)
	{
		if (frame != 0)
			data->gun[frame]->enabled = false;
		if (frame == 1)
			data->gun[0]->enabled = false;
		if (++frame > 4)
		{
			frame = 0;
			shooting = false;
		}
		data->gun[frame]->enabled = true;
	}
	data->renderer.changed = true;
}
