/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 14:07:29 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	main(int ac, char **av, char **ev)
{
	int		i;
	int		pid_i;
	t_fds	fds;
	pid_t	*pids;

	if (ac >= 5)
	{
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
		return (0);
	}
	error_mes("pipex", "Bad argments");
}
