/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:51:48 by rakropp           #+#    #+#             */
/*   Updated: 2024/08/21 14:40:24 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_env(t_data *data, t_node *node)
{
	if (ms_strncmp(node->cmd[0], "env\0", 4))
		ms_error(data, "eidexe/env.c 18: invalid argument(s)", EINVAL);
	if (node->cmd[1])
		ms_error(data, "eidexe/env.c 20: too many arguments for function call", EIO);
	env_print(data);
	g_lastexit = 0;
}
