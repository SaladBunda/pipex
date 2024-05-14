/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/14 19:45:18 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void first_arg(char **av,t_pipx *pipx, int count)
{
	if(count == 0)
	{
		pipx->infile = open(av[1], O_RDONLY);
		if (pipx->infile == -1)
		{
			perror("Infile");
			exit(EXIT_FAILURE);
		}
		pipx->outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
		if(pipx->outfile == -1)
		{
			perror("outfile:");
			exit(EXIT_FAILURE);
		}
	}
	return ;
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

char **check_args(int count, char **av, char **env, t_pipx *pipx)
{
	// int flag = 0;
	char **cmd;
	int index = 0;
	
	first_arg(av,pipx,count);
	cmd = second_arg(av,count + 2);
	find_path(env,&index);
	pipx->command = ft_split(env[index],':');
	pipx->command[0]=ft_strtrim(pipx->command[0],"PATH=");
	// if(access(cmd[0],X_OK) != -1)
	// 	return cmd;
	while(pipx->command[pipx->pos])
	{
		if(access(ft_strjoin_p(pipx->command[pipx->pos],cmd[0]),X_OK) != -1)
			break;
			// flag = 1;
		pipx->pos++;
	}
	if(pipx->command[pipx->pos] == NULL)
		exit(127);
	return cmd;
}

void init_pipx(t_pipx *pipx,t_pipx *pipx2)
{
		pipx->command = NULL;
		pipx->param = NULL;
		pipx->pos = 0;
		pipx2->command = NULL;
		pipx2->param = NULL;
		pipx2->pos = 0;
}

int main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		t_pipx pipx1;
		t_pipx pipx2;
		init_pipx(&pipx1,&pipx2);
		// char **comd;
		// char **comd2;
		// char **cmd1 = NULL;
		// char **cmd2 = NULL;
		int fid[2];
		int pfd[2];
		// int i = 0;
		// int j = 0;
		// int pid[2];
		pipx1.param = check_args(0,av,env,&pipx1);
		pipx2.param = check_args(1,av,env,&pipx2);
		// pipx1.outfile = open(av[4], O_RDWR | O_CREAT | O_APPEND, 0644);
		// if(pipx1.outfile == -1)
		// {
		// 	perror("infile:");
		// 	exit(EXIT_FAILURE);
		// }
		// pipx1.infile = open(av[1],O_RDONLY);
		// if(pipx1.infile == -1)
		// {
		// 	perror("infile:");
		// 	exit(EXIT_FAILURE);
			
		// }
		if(pipe(pfd) == -1)
			return (perror("pipe\n"),1);
		fid[0] = fork();
		if(fid[0] == -1)
		{
			perror("Fork:");
			exit(EXIT_FAILURE);
		}
		if(fid[0] == 0)
		{
			dup2(pipx1.infile,STDIN_FILENO);
			close(pipx1.infile);
			close(pfd[0]);
			dup2(pfd[1],STDOUT_FILENO);
			if(execve(ft_strjoin_p(pipx1.command[pipx1.pos],pipx1.param[0]),pipx1.param,env) == -1)
			{
				perror("execv:");
				exit(EXIT_FAILURE);	
			}
			close(pfd[1]);
			exit(EXIT_SUCCESS);
		}

		fid[1] = fork();
		if(fid[1] == -1)
		{
			perror("Fork2:");
			exit(EXIT_FAILURE);
		}
		if(fid[1] == 0)
		{
			close(pipx1.infile);
			close(pfd[1]);
			dup2(pfd[0],STDIN_FILENO);
			close(pfd[0]);
			dup2(pipx1.outfile,STDOUT_FILENO);
			if(execve(ft_strjoin_p(pipx2.command[pipx2.pos],pipx2.param[0]),pipx2.param,env) == -1)
			{
				perror("execv2:");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		close(pfd[1]);
		close(pfd[0]);
		close(pipx1.outfile);
		close(pipx1.infile);
		while(wait(NULL) > 0);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}