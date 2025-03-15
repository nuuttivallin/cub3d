/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:44:15 by cesasanc          #+#    #+#             */
/*   Updated: 2024/11/08 13:07:46 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Function to print error message and exit the program */
void	error_exit(t_data *data, char *str, int status)
{
	print_error(str);
	clean_exit(data, status);
}

/* Function to print error message in stderr */
void	print_error(char *str)
{
	if (str)
	{
		ft_putstr_fd("Cub3d Error: ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
	}
	ft_putstr_fd("\n", STDERR_FILENO);
}

/* Function to free the map array, textures and data */
void	ft_free_data(t_data **info)
{
	if ((*info)->north_texture)
		mlx_delete_texture((*info)->north_texture);
	if ((*info)->south_texture)
		mlx_delete_texture((*info)->south_texture);
	if ((*info)->west_texture)
		mlx_delete_texture((*info)->west_texture);
	if ((*info)->east_texture)
		mlx_delete_texture((*info)->east_texture);
	if ((*info)->map)
		ft_free_array((*info)->map);
	if (*info)
	{
		free(*info);
		*info = NULL;
	}
}

/* Function to delete the textures and images and close the window */
void	clean_data(t_data *data)
{
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx)
	{
		mlx_close_window(data->mlx);
		mlx_terminate(data->mlx);
	}
	ft_free_data(&data);
}

/* Function to free the array */
void	clean_exit(t_data *data, int status)
{
	if (!data)
		exit(status);
	clean_data(data);
	exit(status);
}
