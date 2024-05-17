/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:25:26 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/17 06:23:26 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = ft_strlen(needle);
	if (!haystack && len == 0 && needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len)
		{
			if (j == count - 1 && needle[j] == haystack[i + j]
				&& haystack[i + j] != '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	file_io(char **av, t_pipx *pipx, int count)
{
	if (count == 0)
	{
		pipx->infile = open(av[1], O_RDONLY);
		if (pipx->infile == -1)
		{
			perror("Infile");
			exit(EXIT_FAILURE);
		}
		pipx->outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (pipx->outfile == -1)
		{
			perror("outfile:");
			exit(EXIT_FAILURE);
		}
	}
}

void	close_fds(int n1, int n2, int n3, int n4)
{
	close(n1);
	close(n2);
	close(n3);
	close(n4);
}
