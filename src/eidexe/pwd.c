/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakropp <rakropp@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:57:58 by rakropp           #+#    #+#             */
/*   Updated: 2024/08/30 12:47:56 by rakropp          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_pwd(t_data *data, t_node *node)
{
	char	*path;
	int		i;

	i = 0;
	if (ms_strncmp(node->cmd[0], "pwd\0", 4))
		ms_error(data, "eidexe/pwd.c 22: invalid argument(s)", EINVAL);
	if (node->cmd[1])
		ms_error(data, "eidexe/pwd.c 24: too many arguments for function call", EIO);
	while (data->env[i])
	{
		if (ms_strncmp(data->env[i], "PWD", 3) == 0)
		{
			path = ms_strdup(data->env[i]); // malloc check
			path = ms_substr(data, path, 4, ms_strlen(path));
		}
		i++;
	}
	printf("%s\n", path);
	free(path);
	data->exe->endline = 1;
	g_lastexit = 0;
}
