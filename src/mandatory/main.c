/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 13:52:17 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

int	main(int ac, char **av, char **ev)
{
	t_fds	fds;
	pid_t	pids[2];

	if (ac == 5)
	{
		fds.o = open_file(av[4], NEW_EMPTY);
		fds.i = open_file(av[1], RDONLY);
		dup_close(fds.i, STDIN_FILENO);
		pids[0] = child_process(av[2], ev);
		dup_close(fds.o, STDOUT_FILENO);
		pids[1] = parent_process(av[3], ev);
		waitpid(pids[0], NULL, 0);
		waitpid(pids[1], NULL, 0);
		return (0);
	}
	error_mes("pipex", "Bad argments");
}
