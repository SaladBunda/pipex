/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:37:11 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/31 22:36:01 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i]; 
		i++;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)c == s[i])
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	count;

	count = ft_strlen(src);
	if (dstsize == 0)
		return (count);
	i = 0;
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (count);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*p;
	size_t	i;
	size_t	size;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	else
		j = ft_strlen(s1) - 1;
	i = 0;
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i++;
	while (j > i && ft_strrchr(set, s1[j]) != 0)
		j--;
	if ((int) j - i + 1 <= 0)
		size = 0;
	else
		size = j - i + 1;
	p = malloc(sizeof(char) * (size + 1));
	if (!p)
		return (NULL);
	ft_strlcpy(p, &s1[i], size + 1);
	return (free(s1), p);
}

char	*fjoin(char *s1, char *s2)
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
	p = (char *)malloc(sizeof(char) * (length + 2));
	if (!p)
		return (NULL);
	while (s1[++i])
		p[i] = s1[i];
	p[i++] = '/';
	while (s2[j])
		p[i++] = s2[j++];
	p[length + 1] = '\0';
	return (p);
}
