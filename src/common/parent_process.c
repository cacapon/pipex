/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:59:13 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 12:56:14 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	parent_process(char *cmd, char **ev)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
		exec(cmd, ev);
	else
		waitpid(pid, NULL, 0);
}
