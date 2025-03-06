/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:19 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/06 16:07:10 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANDATORY_H
# define MANDATORY_H

// library
# include <sys/wait.h>

// custom include
# include "common.h"

// struct
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