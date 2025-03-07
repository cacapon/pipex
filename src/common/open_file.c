/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:13:59 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 13:21:21 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

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
	{
		error_mes(f_path, "open failed");
		exit(EXIT_FAILURE);
	}
	return (f);
}
