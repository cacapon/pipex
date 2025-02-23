/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 12:31:09 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/23 13:21:20 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_COMMAND_PATH_H
# define GET_COMMAND_PATH_H
# include "libft.h"
# include <stddef.h>

char	*get_command_path(char *cmd, char **envp);

#endif