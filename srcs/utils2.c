/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 22:25:26 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/04/24 22:37:42 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin_p(char *s1, char *s2)
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