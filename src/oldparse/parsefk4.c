/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 10:09:17 by jbober            #+#    #+#             */
/*   Updated: 2024/08/29 14:56:54 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Expands all available $* in each node unless tied to export/unset
 */
void	m_sexpand(t_data *data, t_list *iamhere)
{
	iamhere = data->lstart;
	while (iamhere)
	{
		ms_expandnode(data, iamhere->content);
		iamhere = iamhere->next;
	}
}

/**
 * Searches the given node for $* and expands it
 */
void	ms_expandnode(t_data *data, t_node *content)
{
	int	k;
	int	i;
	int	moda;
	int	modb;
	
	k = 0;
	while (content->cmd[k])
	{
		i = 0;
		moda = 0;
		modb = 0;
		while (content->cmd[k][i])
		{
			if ((content->cmd[k][i] == 34) && (modb % 2 == 0))
				moda++;
			if ((content->cmd[k][i] == 39) && (moda % 2 == 0))
				modb++;
			if ((content->cmd[k][i] == 36) && (modb % 2 == 0))
				i = ms_getexpansion(data, content, k, i);
			i++;
		}
		k++;
	}
}

/**
 * replaces in content->cmd[k] "bla $COLORTERM" with "bla truecolor"
 */
int	ms_getexpansion(t_data *data, t_node *content, int k, int l)
{
	char	*expanded;
	char	*tmp;
	int		lenxpanded;
	int		lentmp;

	tmp = ms_strdup(data, content->cmd[k]);
	expanded = ms_getexpanded(data, tmp, content->cmd[k], l);
	if (!expanded)
	{
		free(tmp);
		return (0);
	}
	hal$test:bla
	ms_countexpansion(content->cmd[k], expanded, tmp, l);
	return (l + lenxpanded);
}

/**
 * more than 25 lines
 */
void	ms_countexpansion(char *str, char *expanded, char *tmp, int l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < l)
	{
		str[i] = tmp[i];
		i++;
	}
	while (i < (l + ms_strlen(expanded)))
	{
		str[i] = expanded[j];
		i++;
		j++;
	}
	while (tmp[i + j])// j falsch
	{
		str[i] = tmp[i + j];
		i++;
	}
	str[i] = '\0';
	free(tmp);
	free(expanded);
}

/**
 * Expands $*
 * If it does not exist, it  
 */
char	*ms_getexpanded(t_data *data, char *tmp, char *str, int l)
{
	int		i;
	int		k;
	int		looklen;
	char	*lookme;

	i = 1;
	if (str[l + i] == 63)
		return (ms_itoa(g_lastexit));
	if (str[l + i] == '\0')
		return (NULL);
	while ((str[l + i]) && (ms_strrchr(" \t\n=:;|&'\"`(){}/$?*@", str[l + i], 0) == -1))
		i++;
	lookme = malloc((i - 1) * sizeof(char));
	if (!lookme)
	{
		free(tmp);
		ms_error(data, "parse/parsefk4.c 139: failloc :(", ENOMEM);
	}
	i = 1;
	while ((str[l + i]) && (ms_strrchr(" \t\n=:;|&'\"`(){}/$?*@", str[l + i], 0) == -1))
	{
		lookme[i - 1] = str[l + i];
		i++;
	}
	lookme[i - 1] = '\0';
	looklen = ms_strlen(lookme);
	k = ms_findexpanse(data, lookme);
	free (lookme);
	// free & malloc content->cmd[k] as tmp - looklen + len strlen(data->env[k] + i) aaaah
	if (k == -1)
		return (NULL);
	lookme = ms_strdup(data, data->env[k] + i);
	return (lookme);
}

// fix echo hello$TERM:hello -> should be helloxterm-256color:hello, is helloxterm-256colorterm-256color


/**
 * Returns the len of $* pointed at by 
 */
		free(content->cmd[k]);
		content->cmd[k] = NULL;
	content->cmd[k] = malloc((ms_strlen(tmp)
		+ lenxpanded + 1) * sizeof(char));//malloc tmp-$w/e
	if (!content->cmd[k])
	{
		free(tmp);
		free(expanded);
		ms_error(data, "parse/parsefk4.c 83: failloc :(", ENOMEM);
	}
	lenxpanded = ms_strlen(expanded);