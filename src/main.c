/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:07:46 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/11 21:51:56 by ttsubo           ###   ########.fr       */
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

void	exec_cmd2(int pipefd[2], char *cmd2, char *file2, char **envp)
{
	int		fd;
	char	**args;
	char	*bin_path;

	fd = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		exit(1);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(pipefd[1]);
	args = ft_split(cmd2, ' ');
	bin_path = get_command_path(args[0], envp);
	execve(bin_path, args, envp);
	exit(1);
}

void exec(char *cmd, char **envp, int in_fd, int out_fd)
{

}

int	file_error_check(int file_fd[3])
{
	int	err_flg;

	err_flg = 0;
	if (file_fd[0] == -1)
    	perror("Error opening input file");
	if (file_fd[1] == -1)
    	perror("Error opening output file");
	if (file_fd[2] == -1)
    	perror("Error opening tmp file");
	if (file_fd[0] == -1 || file_fd[1] == -1 || file_fd[2] == -1)
	{
		err_flg = 1;
		if (file_fd[0] != -1)
			close(file_fd[0]);
		if (file_fd[1] != -1)
			close(file_fd[1]);
		if (file_fd[2] != -1)
			close(file_fd[2]);
	}
	return (err_flg);	
}

int	main(int argc, char **argv, char **envp)
{
	int	file_fd[3];

	file_fd[0] = open(argv[1], O_RDONLY);
	file_fd[1] = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	file_fd[2] = open("/tmp", O_TMPFILE | O_RDWR, 0600);
	if (file_error_check(file_fd))
		return (1);
	if (argc != 5)
		return (1);	
	if (fork() == 0)
		exec(argv[2], envp, file_fd[0], file_fd[2]);
	if (fork() == 0)
		exec(argv[3], envp, file_fd[2], file_fd[3]);
	return (0);
}
