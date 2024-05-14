/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:02:24 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/02 18:09:56 by ael-maaz         ###   ########.fr       */
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
	char **command;
	char **param;
	int position;
    int infile;
    int outfile;

} t_pipx;

/*get next line functions*/
char	*get_next_line(int fd);
int		ft_strchr_g(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *s);
void	*ft_memfunc(void *b, void *s, int c, size_t len);
/*ft_split functions*/
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	**ft_split(char const *s, char c);
/* extra functions */
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin_p(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c);
void function1(const char *s, int *i);

#endif