/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:53:13 by rakropp           #+#    #+#             */
/*   Updated: 2024/10/14 10:40:55 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_export(t_data *data, char **arg, char **str, int start)
{
	int	c;

	c = 0;
	while (str[start])
	{
		if (ms_strrchr(str[start], '=', 0) != -1)
			arg[c++] = ms_strdup(str[start++]); // malloc check
		else
		{
			start++;
			arg[c++] = ms_strdup(" \0"); // malloc check
		}
	}
	arg[c] = NULL;
	if (data->pid)//silent DataNotUsed-error
		c = 1;
}

void	ms_export(t_data *data, t_node *node)
{
	char	**export;
	int		c;

	c = 0;
	if (!(ms_strncmp(node->cmd[c], "export", 5)))
		c++;
	if (!(ms_arglen(node->cmd, c)))
		env_print(data);
	else
	{
		export = malloc((ms_arglen(node->cmd, c) + 1) * sizeof(char *));
		if (!export)
			ms_error(data, "eidexe/export.c 47: failloc :(", ENOMEM);
		fill_export(data, export, node->cmd, c);
		data->env = add_env(data, export);
	}
	g_lastexit = 0;
}

// nimmt ""''
// nimmt $*
// overwriting existing stuff
// Checken vor dem Ding