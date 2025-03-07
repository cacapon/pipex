/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:02:04 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 12:02:09 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

void	exec(char *cmd, char **envp)
{
	char	*bin_path;
	char	**cmds;

	cmds = ft_split(cmd, ' ');
	if (!cmds)
		error("split failed");
	bin_path = get_cmd_path(cmds[0], envp);
	if (!bin_path)
	{
		ft_putstr_fd(cmds[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exec_free(bin_path, cmds);
		exit(1);
	}
	if (execve(bin_path, cmds, envp) == -1)
	{
		error(cmds[0]);
		exec_free(bin_path, cmds);
	}
	exit(1);
}
