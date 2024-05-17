/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 06:23:51 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/17 06:25:35 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_pipx(t_pipx *pipx, t_pipx *pipx2)
{
	pipx->cmd = NULL;
	pipx->prm = NULL;
	pipx->pos = 0;
	pipx2->cmd = NULL;
	pipx2->prm = NULL;
	pipx2->pos = 0;
}

char	**second_arg(char **av, int option)
{
	char	**cmd;
	int		i;

	i = -1;
	cmd = ft_split(av[option], ' ');
	while (cmd[++i])
	{
		cmd[i] = ft_strtrim(cmd[i], "\'\"");
	}
	return (cmd);
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
