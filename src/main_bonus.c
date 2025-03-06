/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/06 15:11:00 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef enum e_ftype
{
	APPEND = 0,
	NEW_EMPTY = 1,
	RDONLY = 2,
} t_ftype;

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

void	error(char *mes)
{
	perror(mes);
	exit(EXIT_FAILURE);
}

int	open_file(char *f_path, t_ftype i)
{
	int	f;

	f = 0;
	if (i == APPEND)
		f = open(f_path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == NEW_EMPTY)
		f = open(f_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == RDONLY)
		f = open(f_path, O_RDONLY, 0777);
	if (f == -1)
		error("open_file: open failed.");
	fprintf(stderr, "open_file: f=%d\n", f);
	return (f);
}


void	exec(char *cmd, char **ev)
{
	int		i;
	char	*bin_path;
	char	**cmds;

	fprintf(stderr, "DEBUG:exec start\n");
	i = -1;
	cmds = ft_split(cmd, ' ');
	bin_path = get_command_path(cmds[0], ev);
	fprintf(stderr, "DEBUG:exec bin_path=%s\n", bin_path);
	if (!bin_path)
	{
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		_exec_free(bin_path, cmds);
		exit(1);
	}
	if (execve(bin_path, cmds, ev) == -1)
		error("exec:execve failed.");
	fprintf(stderr, "DEBUG:exec done\n");
}

void	child_process(char *cmd, char **ev)
{
	pid_t	pid;
	int		fd[2];

	fprintf(stderr, "DEBUG:child start\n");
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
	fprintf(stderr, "DEBUG:child done\n");
}

int	main(int ac, char **av, char **ev)
{
	int	i;
	int	f_in;
	int f_out;

	fprintf(stderr, "DEBUG:main start\n");
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
	fprintf(stderr, "DEBUG:main done\n");
	error("Error: Bad argment");
}