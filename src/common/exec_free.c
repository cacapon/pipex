/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:24:22 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/06 16:25:13 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	exec_free(char *bin_path, char **args)
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
