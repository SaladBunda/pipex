/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:42:20 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/31 22:47:35 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	file_io_hd(char **av, t_pipx *pipx, int current)
{
	if (current == 0)
	{
		pipx->infile = open("here_doc.txt", O_RDONLY, 0644);
		if (pipx->infile == -1)
		{
			perror("Infile:");
			exit(EXIT_FAILURE);
		}
		pipx->outfile = open(av[pipx->info + 1], CR | RD | TR, 0644);
		if (pipx->outfile == -1)
		{
			perror("outfile:");
			exit(EXIT_FAILURE);
		}
	}
}

char	**check_args_hd(int current, char **av, char **env, t_pipx *px)
{
	char	**cmd;
	char	*str;
	int		index;

	index = 0;
	file_io_hd(av, px, current);
	cmd = second_arg(av, current + 3);
	find_path(env, &index);
	px->cmd = ft_split(env[index], ':');
	px->cmd[0] = ft_strtrim(px->cmd[0], "PATH=");
	if (access(cmd[0], X_OK) != -1)
		return (px->cmd[0] = NULL, cmd);
	while (px->cmd[px->pos])
	{
		str = fjoin(px->cmd[px->pos], cmd[0]);
		if (access(str, X_OK) != -1)
			break ;
		px->pos++;
		free(str);
	}
	if (px->cmd[px->pos] == NULL)
		exit(127);
	free(str);
	return (cmd);
}

void	child_hd(t_pipx *p, int c, int **pipe_id, t_input io)
{
	if (c != 0 && c != io.ac - 4)
	{
		dup2(pipe_id[c - 1][0], STDIN_FILENO);
		dup2(pipe_id[c][1], STDOUT_FILENO);
		close(pipe_id[c - 1][0]);
		close(pipe_id[c - 1][1]);
	}
	else if (c == 0)
	{
		dup2(p[0].infile, STDIN_FILENO);
		dup2(pipe_id[c][1], STDOUT_FILENO);
		close(p[0].infile);
	}
	else
	{
		dup2(p[0].outfile, STDOUT_FILENO);
		dup2(pipe_id[c - 1][0], STDIN_FILENO);
		close(p[0].outfile);
		close(pipe_id[c - 1][1]);
		close(pipe_id[c - 1][0]);
	}
	close(pipe_id[c][0]);
	close(pipe_id[c][1]);
	if (execve(fjoin(p[c].cmd[p[c].pos], p[c].pm[0]), p[c].pm, io.env) == -1)
		print_error("execve", 1);
}

void	loop_hd(t_pipx *px, int *fork_id, int **pipe_id, t_input input)
{
	int	count;

	count = 0;
	while (count < input.ac - 3)
	{
		px[count].pm = check_args_hd(count, input.av, input.env, &px[count]);
		if (pipe(pipe_id[count]) == -1)
			print_error("Pipe", 1);
		fork_id[count] = fork();
		if (fork_id[count] == -1)
			print_error("Fork", 1);
		if (fork_id[count] == 0) 
			child_hd(px, count, pipe_id, input);
		else 
		{
			if (count > 0)
			{
				close(pipe_id[count - 1][0]);
				close(pipe_id[count - 1][1]);
			}
			count++;
		}
	}
}

void	reading(char *limiter)
{
	char	*line;
	int		result;
	char	*str;
	int		here_doc;

	here_doc = open("here_doc.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		line = get_next_line(0);
		str = ft_strjoin(limiter, "\n");
		if (!line)
			break ;
		result = fcmp(line, str);
		if (result == 0)
			break ;
		write(here_doc, line, ft_strlen(line));
		free(line);
		free(str);
	}
	free(str);
	free(line);
	close(here_doc);
}
