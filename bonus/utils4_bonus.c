/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:54:24 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/05/27 18:49:20 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_input	init_input(int ac, char **av, char **env)
{
	t_input	tmp;

	tmp.ac = ac;
	tmp.av = av;
	tmp.env = env;
	return (tmp);
}
