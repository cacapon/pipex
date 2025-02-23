/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:31:09 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/23 12:38:32 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_COMMAND_PATH_H
# define GET_COMMAND_PATH_H
# include "libft.h"
# include "get_path.h"
# include <stddef.h>

char	*get_command_path(char *cmd, char **envp);

#endif