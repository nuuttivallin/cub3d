/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:22:01 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:10:04 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to initialize the hooks and loops */
void	hooks_n_loops(t_data *data)
{
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(data->mlx, &cursor_hook, data);
	mlx_close_hook(data->mlx, &close_program, data);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop_hook(data->mlx, &ft_move_hook, (void *)data);
	mlx_loop_hook(data->mlx, &ft_shoot, (void *)data);
	mlx_loop(data->mlx);
}

/* Function to initialize the textures and images of doors, enemies and the
minimap */
int	ft_init_textures(t_data *data)
{
	if (ft_get_door_texture(data) || get_enemy_texture(data))
		return (1);
	data->map_wall = mlx_texture_to_image(data->mlx, data->east_texture);
	if (!data->map_wall || !mlx_resize_image(data->map_wall, 16, 16))
	{
		perror("minimap wall");
		return (1);
	}
	data->map_frame = mlx_texture_to_image(data->mlx, data->north_texture);
	if (!data->map_frame || !mlx_resize_image(data->map_frame, 16, 16))
	{
		perror("minimap frame");
		return (1);
	}
	if (load_frames(data))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = handle_args(argc, argv, data);
	if (!data)
		return (1);
	win_init(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1 || \
		ft_init_textures(data) || ft_draw_minimap_background(data) || \
		ft_draw_minimap_frame(data))
		clean_exit(data, 1);
	if (draw_minimap(data, 250, 250))
	{
		perror("draw_minimap");
		clean_exit(data, 1);
	}
	if (ft_draw_player_to_minimap(data))
	{
		perror("ft_draw_player_to_minimap");
		clean_exit(data, 1);
	}
	place_enemies(data);
	hooks_n_loops(data);
	mlx_terminate(data->mlx);
	return (0);
}
