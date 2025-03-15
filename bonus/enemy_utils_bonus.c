/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:17:08 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:09:51 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Helper function to display the "YOU WIN!" message */
void	you_win(t_data *data)
{
	if (!data->enemy_count && !data->you_win)
	{
		data->you_win = mlx_put_string(data->mlx, "YOU WIN!", WIDTH / 2.5, \
		HEIGHT / 2.5);
		mlx_resize_image(data->you_win, 500, 200);
	}
}
