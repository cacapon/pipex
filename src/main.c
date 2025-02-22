/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/22 10:44:09 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	int		i;

	path = get_path(envp);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		full_path = ft_calloc(1, ft_strlen(dirs[i]) + ft_strlen(cmd) + 2);
		full_path = ft_strjoin(dirs[i], "/");
		full_path = ft_strjoin(full_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	exec_common(t_fds fds, char *cmd, char **envp)
{
	char	*bin_path;
	char	**args;

	dup2(fds.in, STDIN_FILENO);
	dup2(fds.out, STDOUT_FILENO);
	close(fds.close);
	args = ft_split(cmd, ' ');
	if (!args)
		exit(1);
	bin_path = get_command_path(args[0], envp);
	execve(bin_path, args, envp);
	exit(1);
}

static int	_err_check(int i_o[2], t_fds *fds)
{
	if (i_o[0] < 0 || i_o[1] < 0)
		return (perror("open"), 1);
	if (pipe(fds->pipe) == -1)
		return (perror("pipe"), 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		i_o[2];
	t_fds	fds;
	pid_t	pid[2];

	if (argc != 5)
		return (1);
	i_o[0] = open(argv[1], O_RDONLY);
	i_o[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (_err_check(i_o, &fds))
		return (1);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		fds = (t_fds){.in = i_o[0], .out = fds.pipe[1], .close = fds.pipe[0]};
		exec_common(fds, argv[2], envp);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		fds = (t_fds){.in = fds.pipe[0], .out = i_o[1], .close = fds.pipe[1]};
		exec_common(fds, argv[3], envp);
	}
	close(fds.pipe[1]);
	close(fds.pipe[0]);
	close(i_o[0]);
	close(i_o[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
