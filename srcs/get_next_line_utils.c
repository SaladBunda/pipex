/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:33:39 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/04/24 22:27:01 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *s)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (s[count] != '\0')
	{
		count++;
	}
	return (count);
}

void	*ft_memfunc(void *b, void *s, int c, size_t len)
{
	size_t	i;

	i = 0;
	if (c == 0)
	{
		while (i < len)
		{
			((unsigned char *)b)[i++] = '\n'; 
		}
		return (b);
	}
	else
	{
		if (!b && !s)
			return (NULL);
		while (i < len)
		{
			((unsigned char *)b)[i] = ((unsigned char *)s)[i]; 
			i++;
		}
		return (b);
	}
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	p = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	length;
	char	*p;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	length = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (length + 1));
	if (!p)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	while (s2[j])
		p[i++] = s2[j++];
	p[length] = '\0';
	return (p);
}

int	ft_strchr_g(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (0);
}
