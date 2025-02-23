/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:19 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/23 11:21:47 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_fds
{
	int	i;
	int	o;
	int	pipe[2];
	int	pipe_result;
}		t_fds;

typedef struct s_exec_fds
{
	int	i;
	int	o;
	int	x;
}		t_exec_fds;

#endif