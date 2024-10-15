/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:11:53 by jbober            #+#    #+#             */
/*   Updated: 2024/10/14 15:21:48 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cpy_env(t_data *data, char **arg)
{
	int		c;

	c = 0;
	while (arg[c])
		c++;
	data->env = malloc((c + 1) * sizeof(char *));
	if (!data->env)
		ms_error(data, "eidexe/envp.c 121: failloc :(", ENOMEM);
	c = 0;
	while (arg[c])
	{
		data->env[c] = ms_strdup(arg[c]);
		c++;
	}
	data->env[c] = NULL;
}

void	ms_envp(t_data *data, char **envp)
{
	data->env = NULL;
	ms_cpy_env(data, envp);
}
