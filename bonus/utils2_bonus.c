/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:25:26 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/31 22:41:33 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	while (i > 0)
	{
		if ((unsigned char)c == s[i])
			return ((char *)s + i);
		i--;
	}
	if (s[i] == (unsigned char)c)
		return ((char *)s + i);
	return (0);
}

void	function1(const char *s, int *i)
{
	if (s[*i] && s[*i] == '\'')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\'')
			(*i)++;
	}
	else if (s[*i] && s[*i] == '\"')
	{
		(*i)++;
		while (s[*i] && s[*i] != '\"')
			(*i)++;
	}
}

char	*ft_strnstr(const char *hay, const char *needle, int len)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = ft_strlen(needle);
	if (!hay && len == 0 && needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)hay);
	while (hay[i] && i < len)
	{
		j = 0;
		while (needle[j] == hay[i + j] && i + j < len)
		{
			if (j == count - 1 && needle[j] == hay[i + j] && hay[i + j] != '\0')
				return ((char *)hay + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	find_path(char **env, int *i)
{
	while (env[*i])
	{
		if (ft_strnstr(env[*i], "PATH=", 5) != NULL)
			return ;
		(*i)++;
	}
}
