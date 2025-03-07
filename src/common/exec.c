/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:02:04 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 13:15:15 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	exec(char *cmd, char **envp)
{
	char	*bin_path;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	if (!cmds)
	{
		error_mes("exec", "split failed");
		exit(EXIT_FAILURE);
	}
	bin_path = get_cmd_path(cmds[0], envp);
	if (!bin_path)
	{
		error_mes(cmds[0], "command not found.");
		exec_free(bin_path, cmds);
		exit(EXIT_FAILURE);
	}
	if (execve(bin_path, cmds, envp) == -1)
	{
		perror(cmds[0]);
		exec_free(bin_path, cmds);
	}
	exit(1);
}
