/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:22:01 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:08:16 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = handle_args(argc, argv, data);
	if (!data)
		return (1);
	win_init(data);
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_close_hook(data->mlx, &close_program, data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		clean_exit(data, 1);
		return (1);
	}
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop_hook(data->mlx, &ft_move_hook, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
