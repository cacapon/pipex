/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 12:58:10 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mandatory.h"

int	main(int ac, char **av, char **ev)
{
	t_fds	fds;

	if (ac == 5)
	{
		fds.o = open_file(av[4], NEW_EMPTY);
		fds.i = open_file(av[1], RDONLY);
		dup_close(fds.i, STDIN_FILENO);
		child_process(av[2], ev);
		dup_close(fds.o, STDOUT_FILENO);
		parent_process(av[3], ev);
		return (0);
	}
	error("Error: Bad argments");
}
