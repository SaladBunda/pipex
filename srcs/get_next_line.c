/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 19:08:58 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/04/24 22:26:58 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_read(int fd, char *buffer, int index)
{
	char	*tmp;
	char	*frees;

	tmp = malloc(sizeof(char) * 100 + 1);
	if (!tmp)
		return (free(buffer), buffer = NULL, NULL);
	while (index > 0)
	{
		index = read(fd, tmp, 100);
		if (index == -1)
			return (free(buffer), free(tmp), NULL);
		if (index != 0)
		{
			tmp[index] = '\0';
			frees = buffer;
			buffer = ft_strjoin(buffer, tmp);
			if (!buffer)
				return (free(frees), free(tmp), NULL);
			free(frees);
			if (ft_strchr_g(buffer, '\n'))
				break ;
		}
	}
	return (free(tmp), buffer);
}

char	*gettline(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	j = -1;
	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) *(i + 1));
	if (!line)
		return (NULL);
	ft_memfunc(line, "", 0, i + 1);
	line[i] = '\0';
	while (++j < i)
		line[j] = buffer[j];
	return (line);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*p;

	if (!s)
		return (NULL);
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (free(s), NULL);
	ft_memfunc(p, s + start, 1, len - start);
	p[len - start] = 0;
	free(s);
	return (p);
}

char	*rest(char *buffer)
{
	char	*rest;
	int		i;

	i = 0;
	if (!buffer)
	{
		free (buffer);
		return (NULL);
	}
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			if (buffer[i + 1] == '\0')
				return (free(buffer), buffer = NULL, NULL);
			rest = ft_substr(buffer, i + 1, ft_strlen(buffer));
			return (rest);
		}
		i++;
	}
	free (buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0 || 100 <= 0 || read(fd, 0, 0) < 0)
		return (free(buffer), buffer = NULL, NULL);
	buffer = ft_read(fd, buffer, 1);
	if (!buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = gettline(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = rest(buffer);
	return (line);
}
