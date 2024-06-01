/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:35:03 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/01 17:33:44 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	file_io(char **av, t_pipx *pipx, int current)
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

char	**second_arg(char **av, int option)
{
	char	**cmd;
	int		i;

	i = -1;
	cmd = ft_split(av[option], ' ');
	while (cmd[++i])
		cmd[i] = ft_strtrim(cmd[i], "\'\"");
	return (cmd);
}

void	init_pipx(t_pipx *pipx, int ac)
{
	int	i;

	i = 0;
	while (i < ac - 3)
	{
		pipx[i].cmd = NULL;
		pipx[i].pm = NULL;
		pipx[i].pos = 0;
		pipx[i].info = ac - 1;
		i++;
	}
}

void	init_variables(t_pipx **pipx, int **fork_id, int ***pipe_id, int ac)
{
	int	i;

	i = 0;
	*pipx = malloc((ac - 3) * sizeof(t_pipx));
	if (!(*pipx))
		exit(EXIT_FAILURE);
	*fork_id = malloc((ac - 3) * sizeof(int));
	if (!(*fork_id))
		exit(EXIT_FAILURE);
	*pipe_id = malloc((ac - 3) * sizeof(int *));
	if (!(*pipe_id))
		exit(EXIT_FAILURE);
	while (i < ac - 3)
	{
		(*pipe_id)[i] = malloc(2 * sizeof(int));
		if (!(*pipe_id)[i])
			exit(EXIT_FAILURE);
		i++;
	}
}

void	print_error(char *str, int code)
{
	perror(str);
	exit(code);
}
