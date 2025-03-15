/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:20:44 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:09:08 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to load the north texture into the data struct */
int	ft_get_north_texture(t_data *info, char *line)
{
	int	i;

	line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	info->north_texture = mlx_load_png(&line[i]);
	if (!info->north_texture)
	{
		write(2, "Error\ninvalid north texture\n", 28);
		return (1);
	}
	return (0);
}

/* Function to load the south texture into the data struct */
int	ft_get_south_texture(t_data *info, char *line)
{
	int	i;

	line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	info->south_texture = mlx_load_png(&line[i]);
	if (!info->south_texture)
	{
		write(2, "Error\ninvalid south texture\n", 28);
		return (1);
	}
	return (0);
}

/* Function to load the west texture into the data struct */
int	ft_get_west_texture(t_data *info, char *line)
{
	int	i;

	line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	info->west_texture = mlx_load_png(&line[i]);
	if (!info->west_texture)
	{
		write(2, "Error\ninvalid west texture\n", 27);
		return (1);
	}
	return (0);
}

/* Function to load the east texture into the data struct */
int	ft_get_east_texture(t_data *info, char *line)
{
	int	i;

	line[ft_strlen(line) - 1] = '\0';
	i = 0;
	while (line[i] == ' ')
		i++;
	info->east_texture = mlx_load_png(&line[i]);
	if (!info->east_texture)
	{
		write(2, "Error\ninvalid east texture\n", 27);
		return (1);
	}
	return (0);
}
