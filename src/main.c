/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/23 12:19:19 by ttsubo           ###   ########.fr       */
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

void	exec(t_exec_fds e_fds, char *cmd, char **envp)
{
	char	*bin_path;
	char	**args;

	dup2(e_fds.i, STDIN_FILENO);
	dup2(e_fds.o, STDOUT_FILENO);
	close(e_fds.x);
	args = ft_split(cmd, ' ');
	if (!args)
		exit(1);
	bin_path = get_command_path(args[0], envp);
	if (execve(bin_path, args, envp) == -1)
		perror(args[0]);
	exit(1);
}

static int	_err_check(t_fds *fds)
{
	if (fds->i < 0 || fds->o < 0)
		return (perror("open"), 1);
	if (fds->pipe_result == -1)
		return (perror("pipe"), 1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_fds	fds;
	pid_t	pid[2];

	if (argc != 5)
		return (1);
	fds.i = open(argv[1], O_RDONLY);
	fds.o = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	fds.pipe_result = pipe(fds.pipe);
	if (_err_check(&fds))
		return (1);
	pid[0] = fork();
	if (pid[0] == 0)
		exec((t_exec_fds){.i = fds.i, .o = fds.pipe[1], .x = fds.pipe[0]},
			argv[2], envp);
	pid[1] = fork();
	if (pid[1] == 0)
		exec((t_exec_fds){.i = fds.pipe[0], .o = fds.o,
			.x = fds.pipe[1]}, argv[3], envp);
	close(fds.pipe[0]);
	close(fds.pipe[1]);
	close(fds.i);
	close(fds.o);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
	return (0);
}
