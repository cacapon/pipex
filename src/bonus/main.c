/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 12:02:41 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

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
		close(f_in);
		while (i < ac - 2)
			child_process(av[i++], ev);
		dup2(f_out, STDOUT_FILENO);
		close(f_out);
		exec(av[ac - 2], ev);
	}
	error("Error: Bad argments");
}
