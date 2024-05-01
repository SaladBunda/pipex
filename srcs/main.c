/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/01 20:52:28 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int first_arg(char **av)
{
	int fd;

	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("Infile");
		exit(1);
	}
	return fd;
}
char **second_arg(char **av)
{
	char **cmd;
	cmd = ft_split(av[2], ' ');
	return cmd;
}
char **check_args(int ac, char **av, char **env, char ***cmd2, int *i)
{
	// (void)env;
	(void)ac;
	
	char **cmd;
	first_arg(av);
	cmd = second_arg(av);
	(*cmd2) = ft_split(env[4],':');
	(*cmd2)[0]=ft_strtrim((*cmd2)[0],"PATH=");
	while((*cmd2)[*i])
	{
		if(access(ft_strjoin_p((*cmd2)[*i],cmd[0]),X_OK) != -1)
		{
			printf("valid command\n");
			break;
		}
		(*i)++;
	}
	printf("path is:%s\n",(*cmd2)[*i]);
	return cmd;
}     

int main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		char **cmd;
		char **cmd2 = NULL;
		int fid;
		int pfd[2];
		int i= 0;
		int outfile = open("outfile.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
		cmd = check_args(ac,av,env,&cmd2,&i);
		printf("main path:%s\n",ft_strjoin_p(cmd2[i],cmd[0]));
		int infile;
		infile = open(av[1],O_RDONLY);
		if(infile == -1)
			return(perror("infile:"),0);
		if(pipe(pfd) == -1)
			return (perror("pipe\n"),1);
		fid = fork();
		if(fid == -1)
		{
			perror("Fork:");
			exit(EXIT_FAILURE);
		}
		if(fid == 0)
		{
			dup2(infile,STDIN_FILENO);
			close(infile);
			// close(pfd[0]);
			// printf("child\n");
			dup2(outfile,STDOUT_FILENO);
			close(outfile);
			execv(ft_strjoin_p(cmd2[i],cmd[0]),cmd);
			return 0;
		}
		// else
		// {
		// 	char str[20];
		close(pfd[1]);
		// 	read(pfd[0],str,6);
		close(pfd[0]);
		// 	printf("parent\n");
		close(outfile);
		close(infile);
		waitpid(0,NULL,0);
		// }
	}
}