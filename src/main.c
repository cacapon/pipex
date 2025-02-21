/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/21 15:54:28 by ttsubo           ###   ########.fr       */
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

void	exec_common(int in, int out, int close_fd, char *cmd, char **envp)
{
	char	*bin_path;
	char	**args;

	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(close_fd);
	args = ft_split(cmd, ' ');
	if (!args)
		exit(1);
	bin_path = get_command_path(args[0], envp);
	execve(bin_path, args, envp);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	int	pipefd[2];
	int	i_o[2];

	if (argc != 5)
		return (1);
	i_o[0] = open(argv[1], O_RDONLY);
	i_o[1] = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (i_o[0] < 0 || i_o[1] < 0)
		return (1);
	pipe(pipefd);
	if (fork() == 0)
		exec_common(i_o[0], pipefd[1], pipefd[0], argv[2], envp);
	if (fork() == 0)
		exec_common(pipefd[0], i_o[1], pipefd[1], argv[3], envp);
	close(pipefd[1]);
	close(pipefd[0]);
	return (0);
}
