/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakropp <rakropp@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:54:18 by jbober            #+#    #+#             */
/*   Updated: 2024/08/30 12:19:30 by rakropp          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_pwd(t_data *data, char *dir)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		if (!(ms_strncmp(data->env[i], "PWD", 3)))
		{
			free(data->env[i]);
			data->env[i] = ms_strjoin("PWD=", dir);
			if (!data->env[i])
				ms_error(data, "eidexe/cd.c 27: failloc :(", ENOMEM);
			return ;
		}
		i++;
	}
	ms_error(data, "eidexe/cd.c 30: env error", 1);
}

void	ms_cd(t_data *data, t_node *node)
{
	int		i;
	char	*path;

	i = 0;
	if (!(ms_strncmp(node->cmd[i], "cd", 2)))
		i++;
	if (ms_arglen(node->cmd, i) > 1)
		ms_error(data, "eidexe/cd.c 42: too many arguments for function call", EIO);
	if (ms_arglen(node->cmd, i) == 0)
	{
		path = getenv("HOME");
		if (chdir(path))
			ms_error(data, "eidexe/cd.c 47: unable to change to home directory", 1);
	}
	else if (chdir(node->cmd[i]))
		ms_error(data, "eidexe/cd.c 52: invalid PATH", 2);
	set_pwd(data, getcwd(NULL, 0));
	g_lastexit = 0;
}
