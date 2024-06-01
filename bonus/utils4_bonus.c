/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:54:24 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/01 22:22:57 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_input	init_input(int ac, char **av, char **env)
{
	t_input	tmp;

	tmp.ac = ac;
	tmp.av = av;
	tmp.env = env;
	return (tmp);
}

int	fcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((unsigned char)s1[i] > (unsigned char)s2[i])
			return (1);
		else if ((unsigned char)s1[i] < (unsigned char)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

void	free_f(t_pipx *px, int count, int *fork_id, int **pipe_id)
{
	int	i;
	int	j;

	i = -1;
	while (++i < count)
	{
		j = -1;
		while (px[i].cmd[++j] != NULL)
		{
			dprintf(2,"%s      %p\n",px[i].cmd[j],px[i].cmd[j]);
			free(px[i].cmd[j]);
		}
		free(px[i].cmd);
		j = -1;
		while (px[i].pm[++j] != NULL)
			free(px[i].pm[j]);
		free(px[i].pm);
		free(pipe_id[i]);
	}
	free(fork_id);
	free(pipe_id);
	free(px);
}

void	init_variables_hd(t_pipx **pipx, int **fork_id, int ***pipe_id, int ac)
{
	int	i;

	i = 0;
	*pipx = malloc((ac - 4) * sizeof(t_pipx));
	if (!(*pipx))
		exit(EXIT_FAILURE);
	*fork_id = malloc((ac - 4) * sizeof(int));
	if (!(*fork_id))
		exit(EXIT_FAILURE);
	*pipe_id = malloc((ac - 4) * sizeof(int *));
	if (!(*pipe_id))
		exit(EXIT_FAILURE);
	while (i <= ac - 4)
	{
		(*pipe_id)[i] = malloc(2 * sizeof(int));
		if (!(*pipe_id)[i])
			exit(EXIT_FAILURE);
		i++;
	}
}
