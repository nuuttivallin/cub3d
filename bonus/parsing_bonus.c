/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:20:31 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/08 13:08:55 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Function to fill the map with dots, and check that the map is surrounded by
walls */
int	ft_flood_fill(t_data *info, int x, int y)
{
	if (y == 0 || y == info->map_height - 1 || x == 0 || \
		info->map[y][x] == '\0')
	{
		ft_parsing_error("map not surrounded by walls");
		return (1);
	}
	if (!ft_is_player(info->map[y][x]) && info->map[y][x] != 'd')
		info->map[y][x] = '.';
	if (info->map[y + 1][x] != '1' && info->map[y + 1][x] != '.' && \
		!ft_is_player(info->map[y + 1][x]) && ft_flood_fill(info, x, y + 1))
		return (1);
	if (info->map[y - 1][x] != '1' && info->map[y - 1][x] != '.' && \
		!ft_is_player(info->map[y - 1][x]) && ft_flood_fill(info, x, y - 1))
		return (1);
	if (info->map[y][x + 1] != '1' && info->map[y][x + 1] != '.' && \
		!ft_is_player(info->map[y][x + 1]) && ft_flood_fill(info, x + 1, y))
		return (1);
	if (info->map[y][x - 1] != '1' && info->map[y][x - 1] != '.' && \
		!ft_is_player(info->map[y][x - 1]) && ft_flood_fill(info, x - 1, y))
		return (1);
	return (0);
}

/* Function to find the player's position in the map and save it in the data
struct */
void	ft_find_player(t_data *info)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (info->map[y][x] != 'N' && info->map[y][x] != 'S' && \
			info->map[y][x] != 'E' && info->map[y][x] != 'W')
	{
		if (info->map[y][x] != '\0')
			x++;
		else
		{
			x = 0;
			y++;
		}
	}
	info->player_pos[0] = y;
	info->player_pos[1] = x;
}

/* Function to get the elements needed for the scene description file */
static int	ft_get_elements(t_data *info, char *line, int *elements)
{
	if ((!ft_strncmp(line, "F ", 2) && \
		!ft_get_floor_color(info, line + 1)) || \
		(!ft_strncmp(line, "C ", 2) && \
		!ft_get_ceiling_color(info, line + 1)) || \
		(!ft_strncmp(line, "NO ", 3) && \
		!ft_get_north_texture(info, line + 2)) || \
		(!ft_strncmp(line, "SO ", 3) && \
		!ft_get_south_texture(info, line + 2)) || \
		(!ft_strncmp(line, "EA ", 3) && \
		!ft_get_east_texture(info, line + 2)) || \
		(!ft_strncmp(line, "WE ", 3) && \
		!ft_get_west_texture(info, line + 2)))
	{
		*elements += 1;
		return (0);
	}
	*elements = -1;
	return (1);
}

/* Check that scene description file contains only the info needed and
	that they're in the right order */
static int	ft_parse_colors_and_textures(t_data *info, int fd)
{
	char	*line;
	int		elements;

	elements = 0;
	line = get_next_line(fd);
	while (line && (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2) \
			|| !ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
			!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3) || \
			line[0] == '\n'))
	{
		if (line[0] != '\n' && ft_get_elements(info, line, &elements))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line && elements != -1 && elements != 6)
		ft_parsing_error("(textures/colors first, then a map)");
	else if (!line && elements != 6)
		ft_parsing_error("missing info (textures, colors, and a map needed)");
	if (elements == 6 && !ft_parse_map(info, fd, &line))
		return (0);
	if (line)
		free(line);
	return (1);
}

/* Function to parse the scene description file. It updates the data struct
with the colors and textures from the file */
int	ft_parse_scene_description(t_data *info, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_free_data(&info);
		write(2, "Error opening scene description file\n", 37);
		return (1);
	}
	if (ft_parse_colors_and_textures(info, fd))
	{
		ft_free_data(&info);
		close(fd);
		return (1);
	}
	info->floor_rgba = get_rgba(info->floor_color[0], info->floor_color[1], \
								info->floor_color[2], 255);
	info->ceiling_rgba = get_rgba(info->ceiling_color[0], \
						info->ceiling_color[1], info->ceiling_color[2], 255);
	close(fd);
	return (0);
}
