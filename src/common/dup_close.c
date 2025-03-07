/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_close.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:13:41 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 12:16:44 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/**
 * @brief oldfdとstdin/stdoutに接続してoldfdを閉じます。
 *
 * @param oldfd
 * @param stdfd
 */
void	dup_close(int oldfd, int stdfd)
{
	dup2(oldfd, stdfd);
	close(oldfd);
}
