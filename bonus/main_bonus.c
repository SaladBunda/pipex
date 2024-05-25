/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/25 21:21:52 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

void	file_io(char **av, t_pipx *pipx)
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

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = ft_strlen(needle);
	if (!haystack && len == 0 && needle)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[i + j] && i + j < len)
		{
			if (j == count - 1 && needle[j] == haystack[i + j]
				&& haystack[i + j] != '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}

void find_path(char **env, int *i)
{
	while(env[*i])
	{
		if(ft_strnstr(env[*i],"PATH=",5) != NULL)
			return ;
		(*i)++;
	}
}

char **check_args(int current, char **av, char **env, t_pipx *pipx)
{

	char **cmd;
	file_io(av,pipx);
	cmd = second_arg(av,current + 2);
	int index = 0;
	find_path(env,&index);
	pipx->cmd= ft_split(env[index],':');
	pipx->cmd[0]=ft_strtrim(pipx->cmd[0],"PATH=");
	if(access(cmd[0],X_OK) != -1)
		return (pipx->cmd[0] = NULL,cmd);
	while(pipx->cmd[pipx->pos])
	{
		if(access(ft_strjoin_p(pipx->cmd[pipx->pos],cmd[0]),X_OK) != -1)
			break;
		pipx->pos++;
	}
	if(pipx->cmd[pipx->pos] == NULL)
		exit(127);
	return cmd;
}     


void init_pipx(t_pipx *pipx,int ac)
{
	int i = 0;
	while(i < ac - 3)
	{
		pipx[i].cmd = NULL;
		pipx[i].pm = NULL;
		pipx[i].pos = 0;
		pipx[i].info = ac - 1;  
		i++;
	}
}

void init_variables(t_pipx **pipx,int **fork_id, int ***pipe_id, int ac)
{
	int	i;

	i = 0;
	*pipx = malloc((ac - 3) * sizeof(t_pipx));
	if (!(*pipx))
		exit(EXIT_FAILURE);
	*fork_id = malloc((ac - 3) * sizeof(int));
	if (!(*fork_id))
		exit(EXIT_FAILURE);
	*pipe_id = malloc((ac - 4) * sizeof(int *));
	if (!(*pipe_id))
		exit(EXIT_FAILURE);
	while (i < ac - 4)
	{
		(*pipe_id)[i] = malloc(2 * sizeof(int));
        if (!(*pipe_id)[i])
            exit(EXIT_FAILURE);
		i++;
	}
}

int main(int ac, char **av, char **env)
{
	t_pipx	pipx[ac - 3];
	int		count;
	int		fork_id[ac - 3];
	int		pipe_id[ac-4][2];
	int outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	int infile = open(av[1],O_RDONLY);
		// while (1);
	if (ac > 4)
	{
		count = 0;
		// init_variables(&pipx, &fork_id, &pipe_id, ac);
		init_pipx(pipx, ac);
		while (count < ac - 3)
		{
			pipx[count].pm = check_args(count, av, env, &pipx[count]);
			if (pipe(pipe_id[count]) == -1)
				return (perror("pipe\n"), 1);
			fork_id[count] = fork();
			if (fork_id[count] == -1)
			{
				perror("Fork");
				exit(EXIT_FAILURE);
			}
			if (fork_id[count] == 0)
			{
				if (count != 0 && count != ac - 4)
				{
					dup2(pipe_id[count - 1][0], STDIN_FILENO);	
					dup2(pipe_id[count][1], STDOUT_FILENO);	
					close(pipe_id[count - 1][0]);
					// close(pipe_id[count - 1][1]);
					// close(pipe_id[count][0]);
					close(pipe_id[count][1]);
				}
				else if(count == 0)
				{
					dup2(infile,STDIN_FILENO);
					dup2(pipe_id[count][1],STDOUT_FILENO);
					close(infile);
					close(pipe_id[count][0]);
					close(pipe_id[count][1]);
				}
				else
				{
					dup2(outfile, STDOUT_FILENO);
					dup2(pipe_id[count -1][0],STDIN_FILENO);
					close(outfile);
					close(pipe_id[count -1][1]);
					close(pipe_id[count -1][0]);
					close(pipe_id[count][1]);
					close(pipe_id[count][0]);
				}

				if (execve(ft_strjoin_p(pipx[count].cmd[pipx[count].pos], pipx[count].pm[0]), pipx[count].pm,env) == -1)
				{
					perror("execv:");
					exit(EXIT_FAILURE);
				}
				exit(EXIT_SUCCESS);
			}
	
			close(pipe_id[count][1]);
			// close(pipe_id[count][0]);
			close(pipe_id[count - 1][1]);
			// close(pipe_id[count - 1][0]);
			// close(infile);
			// if(count == ac - 4)
			// 	close(outfile);
			count++;
		}
		for(int c = 0;c < ac -3;c++)
        	while (wait(NULL) > 0);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}