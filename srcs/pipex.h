/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:02:24 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/17 07:48:57 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>

typedef struct s_pipx
{
	char	**cmd;
	char	**prm;
	int		pos;
	int		infile;
	int		outfile;

}	t_pipx;

char	*ft_strdup(const char *s1);
int		ft_strlen(const char *s);
/*ft_split functions*/
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
/* extra functions */
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char *s1, char const *set);
char	*fjoin(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c);
void	function1(const char *s, int *i);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
void	file_io(char **av, t_pipx *pipx, int count);
void	init_pipx(t_pipx *pipx, t_pipx *pipx2);
void	find_path(char **env, int *i);
char	**second_arg(char **av, int option);
void	close_fds(int n1, int n2, int n3, int n4);
void freeing(t_pipx *pipx1, t_pipx *pipx2);

#endif