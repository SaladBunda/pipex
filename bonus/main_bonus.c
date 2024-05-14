/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/14 00:31:31 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <stdio.h>

int first_arg(char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Infile");
		exit(EXIT_FAILURE);
	}
	return fd;
}
char **second_arg(char **av, int option)
{
	char **cmd;
	int i = -1;
	cmd = ft_split(av[option], ' ');
	while(cmd[++i])
	{
		cmd[i] = ft_strtrim(cmd[i],"\'\"");
	}
	return cmd;
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
	// int flag = 0;
	
	char **cmd;
	first_arg(av);
	cmd = second_arg(av,current + 2);
	int index = 0;
	find_path(env,&index);
	pipx->command= ft_split(env[index],':');
	pipx->command[0]=ft_strtrim(pipx->command[0],"PATH=");
	while(pipx->command[pipx->position])
	{
		if(access(ft_strjoin_p(pipx->command[pipx->position],cmd[0]),X_OK) != -1)
			break;
		pipx->position++;
	}

	return cmd;
}     


void init_pipx(t_pipx *pipx,int ac)
{
	int i = 0;
	while(i < ac - 3)
	{
		pipx[i].command = NULL;
		pipx[i].param = NULL;
		pipx[i].position = 0;
		i++;
	}
}

// int main(int ac, char **av, char **env)
// {
// 	if (ac > 3)
// 	{
// 		t_pipx pipx[ac - 3];
// 		int count = 0;
// 		int fork_id[ac - 3];
// 		int pipe_id[ac - 4][2];
// 		init_pipx(pipx,ac);
// 		while(count < ac - 3)
// 		{
// 			pipx[count].param = check_args(count,av,env,&pipx[count]);
// 			pipx[count].outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
// 			if(pipx[count].outfile == -1)
// 			{
// 				perror("outfile");
// 				exit(EXIT_FAILURE);
// 			}
// 			pipx[count].infile = open(av[1],O_RDONLY);
// 			if(pipx[count].infile == -1)
// 			{
// 				perror("infile");
// 				exit(EXIT_FAILURE);
				
// 			}
// 			if(pipe(pipe_id[count]) == -1)
// 				return (perror("pipe\n"),1);
// 			// printf("pfd[0]:%d    pfd[1]:%d\n",pfd[0],pfd[1]);
// 			fork_id[count] = fork();
// 			if(fork_id[count]== -1)
// 			{
// 				perror("Fork:");
// 				exit(EXIT_FAILURE);
// 			}
// 			if(fork_id[count] == 0)
// 			{
// 				if (count != 0) 
// 				{ // Not the first command
// 				// Redirect stdin to the read end of the pipe from the previous command
// 					dup2(pipe_id[count - 1][0], STDIN_FILENO);
// 					close(pipe_id[count - 1][0]);
// 				}

// 				if (count != ac - 4) { // Not the last command
// 					// Redirect stdout to the write end of the current pipe
// 					dup2(pipe_id[count][1], STDOUT_FILENO);
// 					close(pipe_id[count][1]);
// 				} else {
// 					// Redirect stdout to the output file
// 					dup2(pipx[count].outfile, STDOUT_FILENO);
// 					close(pipx[count].outfile);
// 				}
// 				dprintf(2,"path:%s\n",pipx[count].command[pipx[count].position]);
// 				dprintf(2,"command:%s\n",pipx[count].param[0]);
// 				for(int j = 0;pipx[count].param[j];j++)
// 					dprintf(2,"param[%d]:%s\n",j,pipx[count].param[j]);
// 				if(execv(ft_strjoin_p(pipx[count].command[pipx[count].position],pipx[count].param[0]),pipx[count].param) == -1)
// 				{
// 					perror("execv:");
// 					exit(EXIT_FAILURE);	
// 				}
// 				exit(EXIT_SUCCESS);
// 			}
// 			close(pipe_id[count][1]);
// 			close(pipe_id[count][0]);
// 			while(wait(NULL) > 0);
// 			count++;
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// 	exit(EXIT_FAILURE);
// }

int main(int ac, char **av, char **env)
{
	if (ac > 3)
	{
		t_pipx pipx[ac - 3];
		int count = 0;
		int fork_id[ac - 3];
		int pipe_id[ac - 4][2];
		init_pipx(pipx, ac);
		while (count < ac - 3)
		{
			pipx[count].param = check_args(count, av, env, &pipx[count]);
			pipx[count].outfile = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (pipx[count].outfile == -1)
			{
				perror("outfile");
				exit(EXIT_FAILURE);
			}
			pipx[count].infile = open(av[1], O_RDONLY);
			if (pipx[count].infile == -1)
			{
				perror("infile");
				exit(EXIT_FAILURE);
			}
			if (pipe(pipe_id[count]) == -1)
				return (perror("pipe\n"), 1);
			fork_id[count] = fork();
			if (fork_id[count] == -1)
			{
				perror("Fork:");
				exit(EXIT_FAILURE);
			}
			if (fork_id[count] == 0)
			{
				if (count != 0)
				{
					dup2(pipe_id[count - 1][0], STDIN_FILENO);	
					close(pipe_id[count - 1][0]);
					close(pipe_id[count - 1][1]);
				}
				if (count != ac - 4)
				{
					dup2(pipe_id[count][1], STDOUT_FILENO);
					close(pipe_id[count][1]);
					close(pipe_id[count][0]);
				}
				else
				{
					dup2(pipx[count].outfile, STDOUT_FILENO);
					close(pipx[count].outfile);
					close(pipe_id[count][0]);
				}
				close(pipx[count].infile); // Close input file descriptor in child process
				close(pipe_id[count][0]);  // Close
				if (execve(ft_strjoin_p(pipx[count].command[pipx[count].position], pipx[count].param[0]), pipx[count].param,env) == -1)
				{
					perror("execv:");
					exit(EXIT_FAILURE);
				}
				dprintf(2,"bunda");
				exit(EXIT_SUCCESS);
			}
			close(pipe_id[count - 1][0]);
			close(pipe_id[count][1]);
			close(pipx[count].outfile);// Close write end of the pipe in parent process
			count++;
		}
			// for (int i = 0; i < ac - 3; i++)
        	// {
        while (wait(NULL) > 0);
                	
        // 	}
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}