/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/27 17:35:53 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"




char **check_args(int current, char **av, char **env, t_pipx *pipx)
{

	char **cmd;
	file_io(av, pipx, current);
	cmd = second_arg(av, current + 2);
	int index = 0;
	find_path(env, &index);
	pipx->cmd = ft_split(env[index], ':');
	pipx->cmd[0] = ft_strtrim(pipx->cmd[0], "PATH=");
	if (access(cmd[0], X_OK) != -1)
		return (pipx->cmd[0] = NULL, cmd);
	while (pipx->cmd[pipx->pos])
	{
		if (access(ft_strjoin_p(pipx->cmd[pipx->pos], cmd[0]), X_OK) != -1)
			break;
		pipx->pos++;
	}
	if (pipx->cmd[pipx->pos] == NULL)
		exit(127);
	return cmd;
}

void init_pipx(t_pipx *pipx, int ac)
{
	int i = 0;
	while (i < ac - 3)
	{
		pipx[i].cmd = NULL;
		pipx[i].pm = NULL;
		pipx[i].pos = 0;
		pipx[i].info = ac - 1;
		i++;
	}
}

void init_variables(t_pipx **pipx, int **fork_id, int ***pipe_id, int ac)
{
	int i;

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
	while (i <= ac - 3)
	{
		(*pipe_id)[i] = malloc(2 * sizeof(int));
		if (!(*pipe_id)[i])
			exit(EXIT_FAILURE);
		i++;
	}
}

void print_error(char *str, int code)
{
	perror(str);
	exit(code);
}


void child(t_pipx *pipx, int count, int **pipe_id, t_input input)
{
	if (count != 0 && count != input.ac - 4)
	{
		dup2(pipe_id[count - 1][0], STDIN_FILENO);
		dup2(pipe_id[count][1], STDOUT_FILENO);
		close(pipe_id[count - 1][0]);
		close(pipe_id[count - 1][1]);
	}
	else if (count == 0)
	{
		dup2(pipx[0].infile, STDIN_FILENO);
		dup2(pipe_id[count][1], STDOUT_FILENO);
		close(pipx[0].infile);
	}
	else
	{
		dup2(pipx[0].outfile, STDOUT_FILENO);
		dup2(pipe_id[count - 1][0], STDIN_FILENO);
		close(pipx[0].outfile);
		close(pipe_id[count - 1][1]);
		close(pipe_id[count - 1][0]);
	}
	close(pipe_id[count][0]);
	close(pipe_id[count][1]);
	if (execve(ft_strjoin_p(pipx[count].cmd[pipx[count].pos], pipx[count].pm[0]), pipx[count].pm, input.env) == -1)
		print_error("execve", 1);
}

void loop(t_pipx *pipx, int *fork_id, int **pipe_id, t_input input)
{
	int count;
	
	count = 0;
	while (count < input.ac - 3)
	{
		pipx[count].pm = check_args(count, input.av, input.env, &pipx[count]);
		if (pipe(pipe_id[count]) == -1)
				print_error("Pipe", 1);
			fork_id[count] = fork();
			if (fork_id[count] == -1)
				print_error("Fork", 1);
			if (fork_id[count] == 0) 
				child(pipx,count,pipe_id,input);
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
t_input init_input(int ac, char ** av, char **env)
{
	t_input tmp;
	tmp.ac = ac;
	tmp.av = av;
	tmp.env = env;
	return tmp;
}

int main(int ac, char **av, char **env)
{
	t_pipx *pipx;
	t_input input;
	int *fork_id;
	int **pipe_id;

	if (ac > 4)
	{
		input = init_input(ac,av,env);
		init_variables(&pipx, &fork_id, &pipe_id, ac);
		init_pipx(pipx, ac);
		loop(pipx,fork_id,pipe_id,input);
		close(pipe_id[ac - 4][0]);
		close(pipx[0].infile);
		close(pipx[0].outfile);
		while (wait(NULL) > 0)
			;

		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}
