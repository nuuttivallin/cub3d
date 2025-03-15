/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:12:14 by nvallin           #+#    #+#             */
/*   Updated: 2023/12/13 17:42:09 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		i2;
	char	*new;

	if (s1 == NULL)
		return (NULL);
	if (s2 == NULL)
	{
		free(s1);
		return (NULL);
	}
	i = gnl_strchr_index(s1, '\0');
	i2 = gnl_strchr_index(s2, '\0');
	new = gnl_strldup(s1, i + i2);
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	i2 = 0;
	while (s2[i2] != '\0')
		new[i++] = s2[i2++];
	new[i] = '\0';
	free(s1);
	return (new);
}

char	*gnl_substr(char *dest, char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	size;

	s_len = 0;
	i = 0;
	if (s != NULL)
	{
		while (s[s_len] != '\0')
			s_len++;
		if (len > s_len - start)
			size = s_len - start;
		else
			size = len;
		if (start > s_len)
			size = 0;
		while (i < size && start < s_len && s[start] != '\0')
			dest[i++] = s[start++];
		dest[i] = '\0';
		return (dest);
	}
	dest[i] = '\0';
	return (dest);
}

int	gnl_strchr_index(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c && s[i] != '\0')
		i++;
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

char	*gnl_strldup(const char *s1, size_t len)
{
	size_t	i;
	char	*dup;

	i = 0;
	dup = malloc(len + 1 * sizeof(char));
	if (!dup)
		return (NULL);
	while (i < len && s1[i] != '\0')
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	gnl_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < n)
		str[i++] = '\0';
}
