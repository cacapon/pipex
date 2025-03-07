/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 13:18:14 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

int	main(int ac, char **av, char **ev)
{
	int		i;
	t_fds	fds;

	if (ac >= 5)
	{
		i = 2;
		fds.o = open_file(av[ac - 1], NEW_EMPTY);
		fds.i = open_file(av[1], RDONLY);
		dup_close(fds.i, STDIN_FILENO);
		while (i < ac - 2)
			child_process(av[i++], ev);
		dup_close(fds.o, STDOUT_FILENO);
		parent_process(av[ac - 2], ev);
		return (0);
	}
	error_mes("pipex", "Bad argments");
}
