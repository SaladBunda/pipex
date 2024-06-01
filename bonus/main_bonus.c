/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/06/01 18:32:27 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**check_args(int current, char **av, char **env, t_pipx *px)
{
	char	**cmd;
	char	*str;
	int		index;

	index = 0;
	file_io(av, px, current);
	cmd = second_arg(av, current + 2);
	int i = -1;
	while(cmd[++i])
		dprintf(2,"%s     %p\n",cmd[i],cmd[i]);
	find_path(env, &index);
	px->cmd = ft_split(env[index], ':');
	str = px->cmd[0];
	px->cmd[0]= ft_strtrim(px->cmd[0], "PATH=");
	free(str);
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

void	child(t_pipx *p, int c, int **pipe_id, t_input io)
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

void	loop(t_pipx *px, int *fork_id, int **pipe_id, t_input input)
{
	int	count;

	count = 0;
	while (count < input.ac - 3)
	{
		px[count].pm = check_args(count, input.av, input.env, &px[count]);
		if (pipe(pipe_id[count]) == -1)
			print_error("Pipe", 1);
		fork_id[count] = fork();
		if (fork_id[count] == -1)
			print_error("Fork", 1);
		if (fork_id[count] == 0) 
			child(px, count, pipe_id, input);			
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



void	here_doc(t_input input)
{
	t_pipx	*px;
	int		*fork_id;
	int		**pipe_id;
	char	*limiter;

	if (input.ac >= 6)
	{
		limiter = ft_strdup(input.av[2]);
		init_variables(&px, &fork_id, &pipe_id, input.ac);
		reading(limiter);
		input.ac--;
		init_pipx(px, input.ac);
		loop_hd(px, fork_id, pipe_id, input);
		close(pipe_id[input.ac - 4][0]);
		close(px[0].infile);
		close(px[0].outfile);
		free(limiter);
		free_f(px,input.ac - 4,fork_id,pipe_id);
		unlink("here_doc.txt");
		exit(EXIT_SUCCESS);
	}
	else
		exit(EXIT_FAILURE);
}
void leaks()
{
	system("leaks pipex");
}
int	main(int ac, char **av, char **env)
{
	t_pipx	*px;
	t_input	input;
	int		*fork_id;
	int		**pipe_id;

	atexit(leaks);
	if (ac > 4)
	{
		input = init_input(ac, av, env);
		if (fcmp(av[1], "here_doc") == 0)
			here_doc(input);
		else
		{
			init_variables(&px, &fork_id, &pipe_id, ac);
			init_pipx(px, ac);
			loop(px, fork_id, pipe_id, input);
			close(pipe_id[ac - 4][0]);
			close(px[0].infile);
			close(px[0].outfile);
			free_f(px,ac - 3,fork_id,pipe_id);
			while (wait(NULL) > 0)
				;
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_FAILURE);
}
