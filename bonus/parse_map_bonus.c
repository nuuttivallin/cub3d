/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:59:55 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:08:44 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Function to allocate memory for the map array and copy the map string into
the array */
static int	ft_get_map(t_data *info, char *map_str)
{
	int	i;
	int	len;

	i = -1;
	info->map = malloc((info->map_height + 1) * sizeof(char *));
	while (info->map && ++i < info->map_height)
	{
		len = gnl_strchr_index(map_str, '\n');
		if (len == -1)
			len = ft_strlen(map_str);
		info->map[i] = gnl_strldup(map_str, len);
		if (!info->map[i])
			break ;
		if (map_str[len] == '\n')
			map_str += (len + 1);
	}
	if (i == info->map_height)
	{
		info->map[i] = NULL;
		ft_find_player(info);
		place_doors(info);
		return (0);
	}
	perror("ft_get_map");
	return (1);
}

/* Function to check if the map content is valid. If the map is not the last
element in the file, the function returns 1. If the map is the last element in
the file, but no player is found, the function returns 1. */
static int	ft_check_map_end(char *map_str, int player_count)
{
	if (player_count == 0)
	{
		ft_parsing_error("no player found");
		return (1);
	}
	while (*map_str == '\n')
		map_str++;
	if (*map_str == '\0')
		return (0);
	if (*map_str != '0' && *map_str != '1' && *map_str != 'N' && \
		*map_str != 'S' && *map_str != 'E' && *map_str != 'W' && \
		*map_str != ' ')
		ft_parsing_error("map has to be the last element in file");
	else
		ft_parsing_error("map can't be seperated by newline");
	return (1);
}

/* Function to check if the amount of players in the map is valid. If the amount
of players is 1, the player position is saved in the data struct. If the amount
of players is more than 1, the function returns 1. */
static int	ft_check_player(t_data *info, int *player_count, int x)
{
	*player_count += 1;
	if (*player_count == 1)
	{
		info->player_pos[0] = info->map_height;
		info->player_pos[1] = x;
		return (0);
	}
	if (*player_count > 1)
		ft_parsing_error("multiple players found");
	return (1);
}

/* Function to check if the map content is valid. If the map content is not
valid, the function returns 1. */
static int	ft_check_map_content(t_data *info, char *map)
{
	int	player;
	int	width;

	width = 0;
	player = 0;
	while (*map)
	{
		while (*map != '\n' && *map != '\0')
		{
			if (!ft_is_valid_content(*map) || (ft_is_player(*map++) && \
				ft_check_player(info, &player, width)))
				return (1);
			width++;
		}
		if (width > info->map_width)
			info->map_width = width;
		width = 0;
		info->map_height++;
		if (*map == '\n' && *++map == '\n')
			break ;
	}
	if (ft_check_map_end(map, player))
		return (1);
	return (0);
}

/* Function to parse the map from the map string */
int	ft_parse_map(t_data *info, int fd, char **line)
{
	char	*map_str;

	map_str = ft_strdup(*line);
	free(*line);
	*line = NULL;
	if (!map_str)
	{
		perror("ft_parse_map");
		return (1);
	}
	if (ft_get_map_str(fd, &map_str) || ft_check_map_content(info, map_str) \
		|| ft_get_map(info, map_str) || \
		ft_flood_fill(info, info->player_pos[1], info->player_pos[0]))
	{
		if (map_str)
			free(map_str);
		return (1);
	}
	free(map_str);
	return (0);
}
