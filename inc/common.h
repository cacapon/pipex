/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:54:18 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/06 16:00:25 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

// define

// includes
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

// structs
typedef enum e_word_type
{
	OUT_WORD,
	IN_WORD,
}		t_word_type;

typedef enum e_ftype
{
	APPEND = 0,
	NEW_EMPTY = 1,
	RDONLY = 2,
}		t_ftype;

// functions
char	**cmd_split(char const *s, char c);
void	error(char *mes);
char	*get_cmd_path(char *cmd, char **envp);
int		open_file(char *f_path, t_ftype i);

#endif