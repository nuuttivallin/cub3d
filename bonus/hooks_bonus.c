/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:45:24 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:09:58 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to handle the cursor movement */
void	cursor_hook(double xpos, double ypos, void *param)
{
	t_data		*data;
	int			x;
	int			y;
	static int	last_pos = -1;

	(void)ypos;
	if (last_pos == -1)
		last_pos = xpos;
	data = param;
	if (xpos - last_pos > 40)
	{
		ft_rotate_player(data, 'r');
		last_pos = xpos;
	}
	else if (xpos - last_pos < -40)
	{
		ft_rotate_player(data, 'l');
		last_pos = xpos;
	}
	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (x < 100 || x > WIDTH - 100)
		mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
}

/* Function to redraw the minimap, including the walls, frame and
mini player */
void	redraw_minimap(t_data *data)
{
	data->map_wall = mlx_texture_to_image(data->mlx, data->east_texture);
	if (!data->map_wall || !mlx_resize_image(data->map_wall, 16, 16))
	{
		print_error("reset game, error getting minimap wall");
		clean_exit(data, 1);
	}
	data->map_frame = mlx_texture_to_image(data->mlx, data->north_texture);
	if (!data->map_frame || !mlx_resize_image(data->map_frame, 16, 16))
	{
		print_error("reset game, error getting minimap frame");
		clean_exit(data, 1);
	}
	if (ft_flood_fill(data, data->player_pos[1], data->player_pos[0]) || \
		ft_draw_minimap_background(data) || ft_draw_minimap_frame(data) || \
		draw_minimap(data, 250, 250) || ft_draw_player_to_minimap(data))
	{
		print_error("reset game, error while redrawing minimap");
		clean_exit(data, 1);
	}
}

/* Function to handle the key presses. If the escape key is pressed, the
program is terminated. If the 'R' key is pressed, the game is reset. If the
'F' key is pressed, the door interaction function is called */
void	key_hook(mlx_key_data_t key_data, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (key_data.key == MLX_KEY_ESCAPE)
	{
		clean_exit(data, 0);
		mlx_close_window(data->mlx);
	}
	if (key_data.key == MLX_KEY_R && key_data.action == MLX_PRESS)
	{
		if (data->you_win)
			mlx_delete_image(data->mlx, data->you_win);
		data->you_win = NULL;
		mlx_delete_image(data->mlx, data->map_wall);
		mlx_delete_image(data->mlx, data->map_frame);
		mlx_delete_image(data->mlx, data->player.mini_player);
		mlx_delete_image(data->mlx, data->map_background);
		ft_init_player(data);
		place_doors(data);
		redraw_minimap(data);
		place_enemies(data);
	}
	if (key_data.key == MLX_KEY_F && key_data.action == MLX_PRESS)
		door_interaction(data);
	data->renderer.changed = true;
}

/* Function to close the window and terminate the mlx instance */
void	close_program(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	exit(EXIT_SUCCESS);
}

/* Function to move the player and rotate the player when the keys are
pressed, and to interact with the doors when the right mouse button is
pressed */
void	ft_move_hook(void *param)
{
	t_data		*data;
	static int	mouse_wait = 0;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		ft_move_player(data, data->player.dir_y, data->player.dir_x);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		ft_move_player(data, -(data->player.dir_x), data->player.dir_y);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		ft_move_player(data, -(data->player.dir_y), -(data->player.dir_x));
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		ft_move_player(data, data->player.dir_x, -(data->player.dir_y));
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		ft_rotate_player(data, 'l');
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		ft_rotate_player(data, 'r');
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_RIGHT) && mouse_wait == 0)
	{
		door_interaction(data);
		mouse_wait = 1;
	}
	if (mouse_wait > 0 && ++mouse_wait > 4)
		mouse_wait = 0;
	data->renderer.changed = true;
}
