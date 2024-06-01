/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:33:39 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/01 21:54:48 by ael-maaz         ###   ########.fr       */
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

void	freeing(t_pipx *pipx1, t_pipx *pipx2)
{
	int	i;

	i = -1;
	while (pipx1->cmd[++i])
		free(pipx1->cmd[i]);
	i = -1;
	while (pipx2->cmd[++i])
		free(pipx2->cmd[i]);
	i = -1;
	while (pipx1->prm[++i])
		free(pipx1->prm[i]);
	i = -1;
	while (pipx2->prm[++i])
		free(pipx2->prm[i]);
}
#include <string.h>

void	print_error(char *str, int code)
{
	if(code == 127)
		write(2,"Pipex: command not found\n",25);
	else
		perror(str);
	exit(code);
}