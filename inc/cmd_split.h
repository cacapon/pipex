/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:59:10 by ttsubo            #+#    #+#             */
/*   Updated: 2025/02/27 13:04:03 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_SPLIT_H
# define CMD_SPLIT_H
# include "libft.h"

typedef enum e_word_type
{
	OUT_WORD,
	IN_WORD,
}		t_word_type;

char	**cmd_split(char const *s, char c);

#endif