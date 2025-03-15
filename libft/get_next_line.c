/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:11:57 by nvallin           #+#    #+#             */
/*   Updated: 2023/12/13 18:29:32 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_nl(int fd, char *buf, char *str, char *next)
{
	int	i;
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		i = 0;
		while (buf[i] != '\0' && buf[i] != '\n')
			i++;
		if (buf[i] != '\n')
		{
			str = gnl_strjoin(str, buf);
			if (str == NULL)
				return (NULL);
			gnl_bzero(buf, BUFFER_SIZE + 1);
			bytes_read = read(fd, buf, BUFFER_SIZE);
		}
		else
		{
			str = gnl_strjoin(str, gnl_substr(next, buf, 0, i + 1));
			next = gnl_substr(next, buf, i + 1, BUFFER_SIZE + 1);
			return (str);
		}
	}
	return (str);
}

static char	*read_file(int fd, char *next, char *str)
{
	char	buf[BUFFER_SIZE + 1];
	int		bytes_read;

	gnl_bzero(buf, BUFFER_SIZE + 1);
	if (read(fd, 0, 0) != -1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			str = find_nl(fd, buf, str, next);
			return (str);
		}
		gnl_bzero(next, BUFFER_SIZE + 1);
		if (str[0] != '\0')
		{
			str = find_nl(fd, buf, str, next);
			return (str);
		}
	}
	free(str);
	return (NULL);
}

static char	*check_next(char *next, char *str)
{
	int	i;

	i = gnl_strchr_index(next, '\n');
	if (i != -1)
	{
		str = gnl_strldup(next, i + 1);
		if (!str)
			return (NULL);
		next = gnl_substr(next, next, i + 1, BUFFER_SIZE + 1);
		return (str);
	}
	else if (next[0] != '\0')
	{
		str = gnl_strldup(next, gnl_strchr_index(next, '\0'));
		if (!str)
			return (NULL);
		gnl_bzero(next, BUFFER_SIZE + 1);
	}
	else
	{
		str = gnl_strldup("", 0);
		if (!str)
			return (NULL);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	next[65534][BUFFER_SIZE + 1];
	char		*str;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 65534)
		return (NULL);
	if (!next[fd][0])
		gnl_bzero(next[fd], BUFFER_SIZE + 1);
	str = NULL;
	str = check_next(next[fd], str);
	if (!str)
		return (NULL);
	i = gnl_strchr_index(str, '\n');
	if (i != -1)
		return (str);
	str = read_file(fd, next[fd], str);
	if (str == NULL)
		gnl_bzero(next[fd], BUFFER_SIZE + 1);
	return (str);
}
