/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:35:03 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/27 17:36:06 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void file_io(char **av, t_pipx *pipx, int current)
{
	if (current == 0)
	{
		pipx->infile = open(av[1], O_RDONLY);
		if (pipx->infile == -1)
		{
			perror("Infile");
			exit(EXIT_FAILURE);
		}
		pipx->outfile = open(av[pipx->info], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (pipx->outfile == -1)
		{
			perror("outfile:");
			exit(EXIT_FAILURE);
		}
	}
}

char **second_arg(char **av, int option)
{
	char **cmd;
	int i;

	i = -1;
	cmd = ft_split(av[option], ' ');
	while (cmd[++i])
		cmd[i] = ft_strtrim(cmd[i], "\'\"");
	return (cmd);
}