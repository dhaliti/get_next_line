/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhaliti <dhaliti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 12:29:18 by dhaliti           #+#    #+#             */
/*   Updated: 2022/03/02 11:57:59 by dhaliti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_read(char *s, int fd)
{
	char	*buffer;
	int		read_bytes;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char *));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(s, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		s = ft_strjoin(s, buffer);
	}
	free(buffer);
	return (s);
}

static char	*ft_get_line(char *s)
{
	int		i;
	char	*get_line;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	get_line = (char *)malloc((i + 2) * sizeof(char));
	if (!get_line)
		return (NULL);
	i = -1;
	while (s[++i] && s[i] != '\n')
		*(get_line + i) = *(s + i);
	if (s[i] == '\n')
	{
		get_line[i] = s[i];
		i++;
	}
	get_line[i] = '\0';
	return (get_line);
}

static char	*ft_leftovers(char *s)
{
	size_t	i;
	size_t	j;
	char	*leftovers;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	leftovers = (char *)malloc((ft_strlen(s + i) + 1) * sizeof(char));
	if (!leftovers)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		*(leftovers + j++) = *(s + i++);
	*(leftovers + j) = '\0';
	free(s);
	return (leftovers);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*s[101];

	if (fd < 0 || fd > 100 || BUFFER_SIZE <= 0)
		return (NULL);
	*(s + fd) = ft_read(*(s + fd), fd);
	if (!*(s + fd))
		return (NULL);
	line = ft_get_line(*(s + fd));
	*(s + fd) = ft_leftovers(*(s + fd));
	return (line);
}
