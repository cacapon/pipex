/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 14:59:11 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static void	here_doc_mode(int ac, char **av, char **ev)
{
	int		out;
	pid_t	pid[2];
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	out = open_file(av[ac - 1], NEW_EMPTY);
	//dup_close(fd[1], STDIN_FILENO);
	line = NULL;
	while (1)
	{
		free(line);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
			break;
		write(fd[1], line, ft_strlen(line));
	}
	free(line);
	pid[0] = child_process(av[3], ev);
	dup_close(out, STDOUT_FILENO);
	pid[1] = parent_process(av[4], ev);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}

static void	multi_pipe_mode(int ac, char **av, char **ev)
{
	int		i;
	int		pid_i;
	t_fds	fds;
	pid_t	*pids;

	i = 2;
	pid_i = 0;
	pids = ft_calloc(ac - 2, sizeof(pid_t));
	fds.o = open_file(av[ac - 1], NEW_EMPTY);
	fds.i = open_file(av[1], RDONLY);
	dup_close(fds.i, STDIN_FILENO);
	while (i < ac - 2)
		pids[pid_i++] = child_process(av[i++], ev);
	dup_close(fds.o, STDOUT_FILENO);
	pids[pid_i++] = parent_process(av[ac - 2], ev);
	while (pid_i > 0)
		waitpid(pids[--pid_i], NULL, 0);
	free(pids);
}

int	main(int ac, char **av, char **ev)
{
	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
			here_doc_mode(ac, av, ev);
		else
			multi_pipe_mode(ac, av, ev);
		return (0);
	}
	error_mes("pipex", "Bad argments");
}
