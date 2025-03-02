/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:27:35 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/02 14:29:38 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_command_path.h"

/**
 * @brief envpの中からPATHから始まる位置を返します。
 * 
 * @param envp 
 * @return int 
 */
static int	_find_path_key_in_envp(char **envp)
{
	//TODO: pathが見つからないときの処理が必要
	int	i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	return (i);
}

/**
 * @brief /bin/cmdの形式になるように文字を結合させます。
 * 
 * @param paths 
 * @param cmd 
 * @return char* 
 */
static char	*_join_path(char **paths, char *cmd)
{
	int		i;
	char	*part_path;
	char	*path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (NULL);
}

/**
 * @brief コマンドのパスを取得します。
 *
 * @param cmd
 * @param envp
 * @return char*
 */
char	*get_command_path(char *cmd, char **envp)
{
	char	**paths;
	int		i;

	//TODO:PATHが見つからないとき別処理が必要
	i = _find_path_key_in_envp(envp);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	return (_join_path(paths, cmd));
}
