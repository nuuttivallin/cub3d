/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:19:27 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:07:51 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* 'Encodes' four individual bytes into an int. */
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

/* Function to initialize the color of the floor from the parsed string */
int	ft_get_floor_color(t_data *info, char *f_color)
{
	int	i;
	int	len;

	i = 0;
	if (info->floor_color[0] != -1)
		ft_parsing_error("multiple floor colors found");
	if (info->floor_color[0] != -1)
		return (1);
	while (*f_color == ' ')
		f_color++;
	while (i < 3 && ft_isdigit(*f_color))
	{
		len = 0;
		while (ft_isdigit(f_color[len]))
			len++;
		if ((i < 2 && f_color[len] != ',') || (i == 2 && f_color[len] != '\n') \
			|| ft_altoi(f_color, len) < 0 || ft_altoi(f_color, len) > 255)
			break ;
		info->floor_color[i++] = ft_altoi(f_color, len);
		f_color = &f_color[len + 1];
	}
	if (i == 3)
		return (0);
	write(2, "Error\ninvalid floor color\n", 26);
	return (1);
}

/* Function to initialize the color of the ceiling from the parsed string */
int	ft_get_ceiling_color(t_data *info, char *c_color)
{
	int	i;
	int	len;

	i = 0;
	if (info->ceiling_color[0] != -1)
		ft_parsing_error("multiple ceiling colors found");
	if (info->ceiling_color[0] != -1)
		return (1);
	while (*c_color == ' ')
		c_color++;
	while (i < 3 && ft_isdigit(*c_color))
	{
		len = 0;
		while (ft_isdigit(c_color[len]))
			len++;
		if ((i < 2 && c_color[len] != ',') || (i == 2 && c_color[len] != '\n') \
			|| ft_altoi(c_color, len) < 0 || ft_altoi(c_color, len) > 255)
			break ;
		info->ceiling_color[i++] = ft_altoi(c_color, len);
		c_color = &c_color[len + 1];
	}
	if (i == 3)
		return (0);
	write(2, "Error\ninvalid ceiling color\n", 28);
	return (1);
}
