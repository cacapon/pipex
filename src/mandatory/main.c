/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 12:02:35 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

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
