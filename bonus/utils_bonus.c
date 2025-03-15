/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:20:56 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:09:12 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Convert len amount of characters in a string to integer */
int	ft_altoi(const char *str, int len)
{
	size_t	result;
	int		sign;
	size_t	max;
	int		i;

	i = 0;
	result = 0;
	sign = 1;
	max = 0 - 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (i < len && str[i] > 47 && str[i] < 58)
	{
		if (result > max / 10 - str[i] - 48 && sign == -1)
			return (0);
		if (result > max / 10 - str[i] - 48 && sign == 1)
			return (-1);
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}

/* Function to free a 2D array */
void	ft_free_array(char **arr)
{
	int	i;

	if (arr && *arr)
	{
		i = 0;
		if (arr != NULL)
		{
			while (arr[i] != NULL)
			{
				free(arr[i]);
				arr[i++] = NULL;
			}
			free(arr);
			arr = NULL;
		}
	}
	else if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

/* Function to print parsing error message */
int	ft_parsing_error(char *message)
{
	write(2, "Error\ninvalid scene description\n", 32);
	if (message)
	{
		ft_putstr_fd(message, 2);
		write(2, "\n", 1);
	}
	return (1);
}

/* Function to check if character is a player */
int	ft_is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/* Function to check if content of the map is valid */
int	ft_is_valid_content(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == '\n' || \
		c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D')
		return (1);
	ft_parsing_error("invalid map content");
	return (0);
}
