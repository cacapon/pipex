/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/06 16:12:04 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void	_exec_free(char *bin_path, char **args)
{
	char	**p;

	free(bin_path);
	if (args)
	{
		p = args;
		while (*p != NULL)
		{
			free(*p);
			p++;
		}
	}
	free(args);
}

void	exec(char *cmd, char **ev)
{
	int		i;
	char	*bin_path;
	char	**cmds;

	i = -1;
	cmds = ft_split(cmd, ' ');
	bin_path = get_cmd_path(cmds[0], ev);
	if (!bin_path)
	{
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		_exec_free(bin_path, cmds);
		exit(1);
	}
	if (execve(bin_path, cmds, ev) == -1)
		error("exec:execve failed.");
}

void	child_process(char *cmd, char **ev)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error("child_process: pipe failed");
	pid = fork();
	if (pid == -1)
		error("child_process: fork failed");
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		exec(cmd, ev);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

int	main(int ac, char **av, char **ev)
{
	int	i;
	int	f_in;
	int	f_out;

	if (ac >= 5)
	{
		i = 2;
		f_out = open_file(av[ac - 1], NEW_EMPTY);
		f_in = open_file(av[1], RDONLY);
		dup2(f_in, STDIN_FILENO);
		while (i < ac - 2)
			child_process(av[i++], ev);
		dup2(f_out, STDOUT_FILENO);
		exec(av[ac - 2], ev);
	}
	error("Error: Bad argment");
}
