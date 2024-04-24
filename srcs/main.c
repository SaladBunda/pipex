/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/04/24 22:40:41 by ael-maaz         ###   ########.fr       */
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
char ** check_args(int ac, char **av, char **env)
{
	// (void)env;
	(void)ac;
	
	char **cmd;
	char **cmd2;
	first_arg(av);
	cmd = second_arg(av);
	cmd2 = ft_split(env[4],':');
	cmd2[0]=ft_strtrim(cmd2[0],"PATH=");
	int i = 0;
	while(cmd2[i])
	{
		if(access(ft_strjoin_p(cmd2[i],cmd[0]),X_OK) != -1)
		{
			printf("valid command\n");
			exit(0);
		}
		i++;
	}
	printf("invalidcommand\n");
	exit(1);
	return cmd;
}

int main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		char **cmd;
		// int fid;
		// int pfd[2];
		cmd = check_args(ac,av,env);
		// if(pipe(pfd) == -1)
		// 	return 1;
		// fid = fork();
		// if(fid == -1)
		// {
		// 	perror("Fork:");
		// 	exit(EXIT_FAILURE);
		// }
		// if(fid == 0)
		// {
		// 	close(pfd[0]);
		// 	write(pfd[1],"bunda\n",6);
		// 	close(pfd[1]);
		// 	printf("child\n");
		// 	execv("/bin/cat",env);
		// 	return 0;
		// }
		// else
		// {
		// 	char str[20];
		// 	close(pfd[1]);
		// 	read(pfd[0],str,6);
		// 	close(pfd[0]);
		// 	printf("parent\n");
		// 	wait(NULL);
		// }
	}
}