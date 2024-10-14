/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:21:17 by jbober            #+#    #+#             */
/*   Updated: 2024/10/14 10:39:28 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_last_exit(t_data *data, char *rest)
{
	char	*tmp;
	char	*ret;

	tmp = ms_itoa(g_lastexit);
	if (!tmp)
		ms_error(data, "eidexe/expand.c 22: failloc :(", ENOMEM);
	ret = ms_strjoin(rest, tmp);
	free (tmp);
	if (!ret)
		ms_error(data, "eidexe/control.c 26: failloc :(", ENOMEM);
	return (ret);
}

char	*let_lose(t_data *data, char *str, int i)
{
	int		c;
	int		t;
	char	*expand;
	char	*ret;
	char	*rest;

	c = 0;
	t = 0;
	expand = ms_substrrev(str, i, ms_strlen(str));
	rest = ms_substr(data, str, 0, i);
	if (expand[0] == '$' && expand[1] == '?')
		return (expand_last_exit(data, rest));
	while (data->env[c])
	{
		if (ms_strncmp(data->env[c], expand, ms_strlen(expand)) == 0)
		{
			while (data->env[c][t] != '=')
				t++;
			ret = ms_strjoin(rest, ms_substr(data, data->env[c], t, ms_strlen(data->env[t])));
			free(expand);
			free(rest);
			free(str);
			if (!ret)
				ms_error(data, "eidexe/expand.c 53: failloc :(", ENOMEM);
			return (ret);
		}
		c++;
	}
	free(expand);
	free(str);
	return (rest);
}

void	ms_expand(t_data *data, t_node *content)
{
	int	c;
	int	i;

	c = 0;
	while (content->cmd[c])
	{
		i = 0;
		while (content->cmd[c][i])
		{
			if (content->cmd[c][i] == '$')
				content->cmd[c] = let_lose(data, content->cmd[c], i);
			i++;
		}
		c++;
	}
}
