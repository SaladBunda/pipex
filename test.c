/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 01:45:08 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/04/24 02:11:47 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

int main(int ac, char **av, char **env)
{
	// char **cmd;
	// int fid;
	// int pfd[2];
	// // cmd = check_args(ac,av,env);
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
	char *cmd[4];
cmd[0]="/bin/ls";
cmd[1]="-l";
cmd[2]="-a";
cmd[3]=NULL;
	int fd[2];
	if(pipe(fd)== -1)
		return 1;
	pid_t pid=fork();
	if(pid == -1)
		return 1;
	if(pid == 0)
	{
		printf("im child1\n");
		dup2(fd[1],STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execv("/bin/ls",cmd);
		perror("command");
	}

char *cmd2[4];
	cmd2[0]="/usr/bin/wc";
	cmd2[1]="-l";
	cmd2[2]=NULL;
	pid_t pid2 = fork();
	if(pid2 == -1)
		return 1;
	if(pid2 == 0)
	{
		printf("im child2\n");
		dup2(fd[0],STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		execv("/usr/bin/wc",cmd2);
		perror("command");
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid,NULL,0);
	waitpid(pid2,NULL,0);
	
}