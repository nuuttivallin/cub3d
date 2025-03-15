/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:05:23 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:09:18 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/*Helper function for drawing the minimap with floodfill*/
int	is_filled(char c, char filling)
{
	if (c == filling || ft_is_player(c) || c == 'D')
		return (1);
	return (0);
}

/*Function to move the door images on the minimap in the y axis*/
void	ft_move_minidoors_y(t_data *data, double direction)
{
	int	i;

	i = 82;
	while (i < (int)data->map_frame->count)
	{
		if (direction > 0)
			data->map_frame->instances[i].y -= 2;
		else
			data->map_frame->instances[i].y += 2;
		if (data->map_frame->instances[i].y > 100 && \
			data->map_frame->instances[i].y < 420 && \
			data->map_frame->instances[i].x > 100 && \
			data->map_frame->instances[i].x < 420 && \
			data->map_frame->instances[i].z == 10)
			data->map_frame->instances[i].enabled = true;
		else
			data->map_frame->instances[i].enabled = false;
		i++;
	}
}

/*Function to move the door images on the minimap in the x axis*/

void	ft_move_minidoors_x(t_data *data, double direction)
{
	int	i;

	i = 82;
	while (i < (int)data->map_frame->count)
	{
		if (direction > 0)
			data->map_frame->instances[i].x -= 2;
		else
			data->map_frame->instances[i].x += 2;
		if (data->map_frame->instances[i].y > 100 && \
			data->map_frame->instances[i].y < 420 && \
			data->map_frame->instances[i].x > 100 && \
			data->map_frame->instances[i].x < 420 && \
			data->map_frame->instances[i].z == 10)
			data->map_frame->instances[i].enabled = true;
		else
			data->map_frame->instances[i].enabled = false;
		i++;
	}
}

/*Function to find the correct instance of the door that the player is facing 
towards in the minimap*/
int	the_door(t_data *data)
{
	int	i;

	i = 82;
	while (i < (int)data->map_frame->count)
	{
		if ((data->player.mini_player->instances[0].y + 8) + \
			data->player.dir_y / 0.1 >= data->map_frame->instances[i].y \
			&& (data->player.mini_player->instances[0].y + 8) + \
			data->player.dir_y / 0.1 <= data->map_frame->instances[i].y + 16 \
			&& (data->player.mini_player->instances[0].x + 8) + \
			data->player.dir_x / 0.1 >= data->map_frame->instances[i].x \
			&& (data->player.mini_player->instances[0].x + 8) + \
			data->player.dir_x / 0.1 <= data->map_frame->instances[i].x + 16)
			break ;
		i++;
	}
	return (i);
}

/*Function to draw the minimap background*/
int	ft_draw_minimap_background(t_data *data)
{
	data->map_background = mlx_new_image(data->mlx, 320, 320);
	if (data->map_background == NULL)
	{
		print_error("minimap background");
		return (1);
	}
	ft_memset(data->map_background->pixels, 124, 320 * 320 * sizeof(int32_t));
	if (mlx_image_to_window(data->mlx, data->map_background, 116, 116) == -1)
	{
		print_error("minimap background");
		return (1);
	}
	mlx_set_instance_depth(&data->map_background->instances[0], 5);
	return (0);
}
