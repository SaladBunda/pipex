/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:01:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/02 14:16:57 by ael-maaz         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
	return fd;
}
char **second_arg(char **av, int option)
{
	char **cmd;
	int i = -1;
	if(option == 1)
		cmd = ft_split(av[2], ' ');
	else
		cmd = ft_split(av[3], ' ');
	while(cmd[++i])
	{
		cmd[i] = ft_strtrim(cmd[i],"\'\"");
		printf("cmd[i]:%s\n",cmd[i]);
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

char **check_args(int ac, char **av, char **env, char ***cmd2, int *i)
{
	// (void)env;
	static int var = 1;
	(void)ac;
	
	char **cmd;
	first_arg(av);
	cmd = second_arg(av,var);
	var++;
	int index = 0;
	find_path(env,&index);
	(*cmd2) = ft_split(env[index],':');
	(*cmd2)[0]=ft_strtrim((*cmd2)[0],"PATH=");
	while((*cmd2)[*i])
	{
		if(access(ft_strjoin_p((*cmd2)[*i],cmd[0]),X_OK) != -1)
		{
			break;
		}
		(*i)++;
	}
	return cmd;
}     

int main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		char **comd;
		char **comd2;
		char **cmd1 = NULL;
		char **cmd2 = NULL;
		int fid;
		int fid2;
		int pfd[2];
		int i = 0;
		int j = 0;
		// int d = 0;
		// printf("%d\n",outfile);
		comd = check_args(ac,av,env,&cmd1,&i);
		comd2 = check_args(ac,av,env,&cmd2,&j);
		// while(comd[d])
		// 	printf("args:%s\n",comd[d++]);
		// printf("args:%s\n",comd[d++]);
		
		int outfile = open(av[4], O_RDWR | O_CREAT | O_APPEND, 0644);
		if(outfile == -1)
		{
			perror("infile:");
			exit(EXIT_FAILURE);
		}
		// printf("main path:%s\n",ft_strjoin_p(cmd1[i],comd[0]));
		int infile;
		infile = open(av[1],O_RDONLY);
		if(infile == -1)
		{
			perror("infile:");
			exit(EXIT_FAILURE);
			
		}
		if(pipe(pfd) == -1)
			return (perror("pipe\n"),1);
		// printf("pfd[0]:%d    pfd[1]:%d\n",pfd[0],pfd[1]);
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
			close(pfd[0]);
			// printf("child\n");
			dup2(pfd[1],STDOUT_FILENO);
			if(execv(ft_strjoin_p(cmd1[i],comd[0]),comd) == -1)
			{
				perror("execv:");
				exit(EXIT_FAILURE);	
			}
			close(pfd[1]);
			return 0;
		}
		waitpid(0,NULL,0);

		fid2 = fork();
		if(fid2 == 0)
		{
			close(pfd[1]);
			dup2(pfd[0],STDIN_FILENO);
			close(pfd[0]);
			dup2(outfile,STDOUT_FILENO);
			if(execv(ft_strjoin_p(cmd2[j],comd2[0]),comd2) == -1)
			{
				perror("execv2:");
				exit(EXIT_FAILURE);
			}
			return 0;
		}

		close(pfd[1]);
		close(pfd[0]);
		close(outfile);
		close(infile);
		waitpid(0,NULL,0);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}