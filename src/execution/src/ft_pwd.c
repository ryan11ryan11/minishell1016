/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 12:32:28 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:15:23 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	ft_pwd2(t_info *info)
// {
// 	char	path[4096];

// 	if (getcwd(path, 4096) != NULL)
// 	{
// 		info->errcode = 0;
// 		return (1);
// 	}
// 	info->errcode = 1;
// 	return (0);
// }

int	ft_pwd(void)
{
	char	path[4096];

	if (getcwd(path, 4096) != NULL)
	{
		ft_putstr_fd (path, 1);
		write (1, "\n", 1);
		return (1);
	}
	return (0);
}
