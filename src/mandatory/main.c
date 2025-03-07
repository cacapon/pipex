/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 11:55:40 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

static void	exec(char *cmd, char **envp)
{
	char	*bin_path;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	if (!cmds)
		error("split failed");
	bin_path = get_cmd_path(cmds[0], envp);
	if (!bin_path)
	{
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exec_free(bin_path, cmds);
		exit(1);
	}
	if (execve(bin_path, cmds, envp) == -1)
	{
		error(cmds[0]);
		exec_free(bin_path, cmds);
	}
	exit(1);
}

void	child_process(char *cmd, char **ev)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error("pipe");
	pid = fork();
	if (pid == -1)
		error("fork");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec(cmd, ev);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_fds	fds;

	if (ac == 5)
	{
		fds.o = open_file(av[ac - 1], NEW_EMPTY);
		fds.i = open_file(av[1], RDONLY);
		dup2(fds.i, STDIN_FILENO);
		close(fds.i);
		child_process(av[2], ev);
		dup2(fds.o, STDOUT_FILENO);
		close(fds.o);
		exec(av[ac - 2], ev);
	}
	error("Error: Bad argments");
}
