/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 22:02:24 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/31 22:45:50 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# define RD O_RDWR
# define CR O_CREAT
# define TR O_TRUNC
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
	char	**pm;
	int		pos;
	int		infile;
	int		outfile;
	int		info;

}	t_pipx;

typedef struct s_input
{
	char	**env;
	char	**av;
	int		ac;
}	t_input;

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
char	*fjoin(char *s1, char *s2);
char	*ft_strrchr(const char *s, int c);
void	function1(const char *s, int *i);
void	file_io(char **av, t_pipx *pipx, int current);
char	**second_arg(char **av, int option);
void	find_path(char **env, int *i);
void	init_pipx(t_pipx *pipx, int ac);
void	init_variables(t_pipx **pipx, int **fork_id, int ***pipe_id, int ac);
void	print_error(char *str, int code);
t_input	init_input(int ac, char **av, char **env);
void	init_var_hd(t_pipx **pipx, int **fork_id, int ***pipe_id, int ac);
int		fcmp(char *s1, char *s2);
void	reading(char *limiter);
void	loop_hd(t_pipx *px, int *fork_id, int **pipe_id, t_input input);

#endif