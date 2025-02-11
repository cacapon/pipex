/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/11 21:03:28 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

char	*get_command_path(char *cmd, char **envp)
{
	char	*path;
	char	**dirs;
	char	*full_path;
	int		i;

	path = getenv("PATH");
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

void	exec_cmd1(int pipefd[2], char *file1, char *cmd1, char **envp)
{
	int		fd;
	char	**args;
	char	*bin_path;

	fd = open(file1, O_RDONLY);
	if (fd < 0)
		exit(1);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	args = ft_split(cmd1, ' ');
	bin_path = get_command_path(args[0], envp);
	execve(bin_path, args, envp);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		pipefd[2];

	if (argc != 5)
		return (1);
	pipe(pipefd);
	ft_printf("DEBUG: %s %s %s %s\n", argv[1], argv[2], argv[3], argv[4]);
	if (fork() == 0)
		exec_cmd1(pipefd, argv[1], argv[2], envp);
	close(pipefd[1]);
	line = get_next_line(pipefd[0]);
	while (line != NULL)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(pipefd[0]);
	}
	return (0);
}
