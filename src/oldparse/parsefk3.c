/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:54:25 by jbober            #+#    #+#             */
/*   Updated: 2024/08/30 18:28:01 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Fills the nodes of a list with commands, seperated by |, and fd-info
 */
void	ms_fillst(t_data *data)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	data->currmds = ms_lstnew(data);
	data->lstart = data->currmds;
	while (data->currstr[k])
	{
		if (data->currstr[k][0] == 124)
		{
			ms_fillnode(data, data->currmds->content, i, k);
			ms_checknode(data, data->currmds->content);
			ms_lstadd_back(data, &data->lstart);
			data->currmds = data->currmds->next;
			i = k + 1;
		}
		k++;
	}
	ms_fillnode(data, data->currmds->content, i, k);
	ms_checknode(data, data->currmds->content);
	data->currmds = data->currmds->next;
	data->currmds = NULL;
}

/**
 * Checks wether the node contains at least one command word
 */
void	ms_checknode(t_data *data, t_node *content)
{
	int	check;
	int	k;

	k = 0;
	check = 0;
	while (content->cmd[k])
	{
		if (ms_strinlst(data, content->cmd[k]) == 1)
			check++;
		k++;
	}
	if (ms_strncmp(content->cmd[0], "./", 2) == 0)
		check++;
	if (check == 0)
	{
		g_lastexit = 2;
		ms_free(data, 1);
		exit(g_lastexit);
	}
}

/**
 * Copies content of **currstr[k] to node
 */
void	ms_cp_to_lst(t_data *data, t_node *content, int k, int c)
{
	int	i;

	i = 0;
	content->cmd[c] = malloc((ms_strlen(data->currstr[k] + 1) * sizeof(char)));
	if (!content->cmd[c])
		ms_error(data, "parse/parsefk3.c 81: failloc :(", ENOMEM);
	while (data->currstr[k][i])
	{
		content->cmd[c][i] = data->currstr[k][i];
		i++;
	}
	content->cmd[c][i] = '\0';
}

/**
 * Fills node with adequate information
 */
void	ms_fillnode(t_data *data, t_node *content, int i, int k)
{
	content->cmd = malloc(((k - i) + 1) * sizeof(char *));
	if (!content->cmd)
		ms_error(data, "parse/parsefk3.c 97: failloc :(", ENOMEM);
	content->path = NULL;
	content->infd = 0;
	content->outfd = 1;
	ms_fillnodext(data, content, i, k);
}

/**
 * More than 25 lines
 */
void	ms_fillnodext(t_data *data, t_node *content, int i, int k)
{
	int	c;

	c = 0;
	while (i < k)
	{
		if ((data->currstr[i][0]) == 60 && (data->currstr[i][1] != 60))
		{
			content->infd = open(data->currstr[i + 1], O_RDONLY);
			if (content->infd < 0)
				ms_error(data, "parse/parsefk3.c 119", ENOENT);
		}
		if (data->currstr[i][0] == 62)
		{
			content->outfd = open(data->currstr[i + 1], O_RDWR | O_CREAT, 0777);
			if (content->outfd < 0)
				ms_error(data, "parse/parsefk3.c 125", ENOENT);
		}
		if ((data->currstr[i][0] == 60 && data->currstr[i][1] == 60)
			|| (data->currstr[i][0] == 62))
		{
			i++;
		}
		else
		{
			ms_cp_to_lst(data, content, i, c);
			c++;
		}
		i++;
	}
	content->cmd[i] = NULL;
}
