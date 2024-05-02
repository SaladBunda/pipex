/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 16:02:02 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/02 14:13:30 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


// static int	word_c(char *str, char c)
// {
// 	int	i;
// 	int	count;

// 	i = 0;
// 	count = 0;
// 	while (str && str[i] == c && str[i])
// 		i++;
// 	while (str && str[i])
// 	{
// 		count++;
// 		while (str[i] != c && str[i])
// 			i++;
// 		while (str[i] == c && str[i])
// 			i++;
// 	}
// 	return (count);
// }

// static char	**freef(char **tab, int j)
// {
// 	while (j >= 0)
// 		free(tab[j--]);
// 	free(tab);
// 	return (NULL);
// }

// static int	char_c(char *str, char c)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] && str[i] != c)
// 		i++;
// 	return (i);
// }

// static char	*strdup_i(const char *s1, char c, int *index)
// {
// 	char	*p;
// 	int		i;
// 	int		j;
// 	int		word_size;

// 	j = 0;
// 	i = *index;
// 	word_size = char_c((char *)&s1[i], c);
// 	p = (char *)malloc(sizeof(char) * (word_size + 1));
// 	if (!p)
// 		return (NULL);
// 	ft_memcpy(p, (char *)s1 + i, (size_t)word_size);
// 	while (j < word_size)
// 	{
// 		j++;
// 		(*index)++;
// 	}
// 	p[word_size] = '\0';
// 	return (p);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**tab;
// 	int		j;
// 	int		i;

// 	i = 0;
// 	j = 0;
// 	if (!s)
// 		return (NULL);
// 	tab = malloc(sizeof(char *) * (word_c((char *)s, c) + 1));
// 	if (!tab)
// 		return (NULL);
// 	while (s[i] && s[i] == c)
// 		i++;
// 	while (s[i] && j < word_c((char *)s, c))
// 	{
// 		tab[j] = strdup_i(s, c, &i);
// 		if (!tab[j])
// 			return (freef(tab, j));
// 		j++;
// 		while (s[i] && s[i] == c)
// 			i++;
// 	}
// 	tab[word_c((char *)s, c)] = NULL;
// 	return (tab);
// }


// int main(int ac, char **av)
// {
// 	char **cmd;
// 	cmd = ft_split(av[1], ' ');
// 	int i = 0;
// 	while(cmd[i])
// 		printf("%s\n",cmd[i++]);
// }

static int	word_c(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i] == c && str[i])
		i++;
	while (str && str[i])
	{
		count++;
		while (str[i] != c && str[i])
		{
			if(str[i] == '\'')
			{
				while(str[++i] != '\'')
					continue ;
			}	
			else if(str[i] == '\"')
			{
				while(str[++i] != '\"')
					continue ;
			}	
			i++;
		}
		while (str[i] == c && str[i])
			i++;
	}
	return (count);
}

static char	**freef(char **tab, int j)
{
	while (j >= 0)
		free(tab[j--]);
	free(tab);
	return (NULL);
}

static int	char_c(char *str, char c)
{
	int	i;

	i = 0;
	if(str[i] == '\'')
	{
		i++;
		while(str[i] && str[i] != '\'')
			i++;
	}
	else if(str[i] == '\"')
	{
		i++;
		while(str[i] && str[i] != '\"')
			i++;
	}
	while (str[i] && str[i] != c)
		i++;
	// printf("word size is:%d\n",i);
	return (i);
}

static char	*strdup_i(const char *s1, char c, int *index)
{
	char	*p;
	int		i;
	int		j;
	int		word_size;

	j = 0;
	i = *index;
	word_size = char_c((char *)&s1[i], c);
	p = (char *)malloc(sizeof(char) * (word_size + 1));
	if (!p)
		return (NULL);
	ft_memcpy(p, (char *)s1 + i, (size_t)word_size);
	while (j < word_size)
	{
		j++;
		(*index)++;
	}
	p[word_size] = '\0';
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (word_c((char *)s, c) + 1));
	if (!tab)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	while (s[i] && j < word_c((char *)s, c))
	{
		tab[j] = strdup_i(s, c, &i);
		if (!tab[j])
			return (freef(tab, j));
		j++;
		if(s[i] && s[i] == '\'')
		{
			i++;
			while(s[i] && s[i] != '\'')
				i++;
		}
		else if (s[i] && s[i] == '\"')
		{
			i++;
			while(s[i] && s[i] != '\"')
				i++;
		}
		while (s[i] && s[i] == c)
			i++;
	}
	tab[word_c((char *)s, c)] = NULL;
	return (tab);
}