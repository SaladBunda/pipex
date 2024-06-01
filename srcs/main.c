/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/01 22:14:00 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**check_args(int count, char **av, char **env, t_pipx *pipx)
{
	char	**cmd;
	int		index;
	char	*str;

	index = 0;
	file_io(av, pipx, count);
	cmd = second_arg(av, count + 2);
	find_path(env, &index);
	pipx->cmd = ft_split(env[index], ':');
	str = pipx->cmd[0];
	pipx->cmd[0] = ft_strtrim(pipx->cmd[0], "PATH=");
	free(str);
	if (access(cmd[0], X_OK) != -1)
		return (free(pipx->cmd[0]),pipx->cmd[0] = NULL, cmd);
	while (pipx->cmd[pipx->pos])
	{
		str = fjoin(pipx->cmd[pipx->pos], cmd[0]);
		if (access(str, X_OK) != -1)
			break ;
		free(str);
		pipx->pos++;
	}
	if (pipx->cmd[pipx->pos] == NULL)
		print_error("Pipex",127);
	free(str);
	return (cmd);
}

void	first_cmd(t_pipx pipx1, char **env, int pfd[2])
{
	dup2(pipx1.infile, STDIN_FILENO);
	close(pipx1.infile);
	close(pfd[0]);
	dup2(pfd[1], STDOUT_FILENO);
	if (execve(fjoin(pipx1.cmd[pipx1.pos], pipx1.prm[0]), pipx1.prm, env) == -1)
	{
		perror("execv:");
		exit(EXIT_FAILURE);
	}
}

void	second_cmd(t_pipx pipx2, char **env, int pfd[2], t_pipx pipx1)
{
	close(pipx1.infile);
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	close(pfd[0]);
	dup2(pipx1.outfile, STDOUT_FILENO);
	if (execve(fjoin(pipx2.cmd[pipx2.pos], pipx2.prm[0]), pipx2.prm, env) == -1)
	{
		perror("execv2:");
		exit(EXIT_FAILURE);
	}
}

void	pipex(t_pipx pipx1, t_pipx pipx2, int pfd[2], char **env)
{
	int	fid[2];

	if (pipe(pfd) == -1)
	{
		perror("pipe\n");
		exit(EXIT_FAILURE);
	}
	fid[0] = fork();
	if (fid[0] == -1)
	{
		perror("Fork:");
		exit(EXIT_FAILURE);
	}
	if (fid[0] == 0)
		first_cmd(pipx1, env, pfd);
	fid[1] = fork();
	if (fid[1] == -1)
	{
		perror("Fork2:");
		exit(EXIT_FAILURE);
	}
	if (fid[1] == 0)
		second_cmd(pipx2, env, pfd, pipx1);
	close_fds(pfd[1], pfd[0], pipx1.outfile, pipx1.infile);
}

int	main(int ac, char **av, char **env)
{
	t_pipx	pipx1;
	t_pipx	pipx2;
	int		pfd[2];

	if (ac == 5)
	{
		init_pipx(&pipx1, &pipx2);
		pipx1.prm = check_args(0, av, env, &pipx1);
		pipx2.prm = check_args(1, av, env, &pipx2);
		pipex(pipx1, pipx2, pfd, env);
		while (wait(NULL) > 0)
			;
		freeing(&pipx1, &pipx2);
		system("leaks pipex");
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
