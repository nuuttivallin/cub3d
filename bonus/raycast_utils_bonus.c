/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:17:01 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:10:32 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to execute the raycasting. It will initialize the ray, set the DDA,
perform the DDA and calculate the wall. */
void	raycast(t_data *data, int x)
{
	init_ray(data, x);
	set_dda(data);
	perform_dda(data);
	calc_wall(data);
}
