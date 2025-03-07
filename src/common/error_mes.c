/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttsubo <ttsubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:51:01 by ttsubo            #+#    #+#             */
/*   Updated: 2025/03/07 13:10:27 by ttsubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

/**
 * @brief ユーザー定義部分のエラー出力をします。
 * 
 * @param mes 
 */
void	error_mes(char *cmd, char *mes)
{
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(mes, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
