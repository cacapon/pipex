/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:59:13 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 13:16:49 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

static void	_error(char *mes)
{
	perror(mes);
	exit(EXIT_FAILURE);
}

void	child_process(char *cmd, char **ev)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		_error("pipe");
	pid = fork();
	if (pid == -1)
		_error("fork");
	if (pid == 0)
	{
		close(fd[0]);
		dup_close(fd[1], STDOUT_FILENO);
		exec(cmd, ev);
	}
	else
	{
		close(fd[1]);
		dup_close(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
