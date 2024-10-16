/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:24:55 by jbober            #+#    #+#             */
/*   Updated: 2024/10/16 17:03:48 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk5_ctrl(t_data *data);
static char	*ms_fillnode(t_data *data, t_node *content, int i, int k);
static int	ms_addsize(t_data *data, int first, int superlast);
static char	*ms_fillnodext(t_data *data, t_node *content, int i, int k);

/**
 * Control structure
 * Creates list with content of data->*currinput
 * Pipe -> new node
 */
char	*ms_parsefk5_ctrl(t_data *data)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	data->currmds = ms_lstnew(data);
	data->lstart = data->currmds;
	while (data->currstr[k])
	{
		if ((data->currstr[k][0] == 124)
			|| (data->currstr[k][0] == 60 && data->currstr[k][1] == 60))
		{
			if (!ms_fillnode(data, data->currmds->content, i, k))
				return (NULL);
			ms_lstadd_back(data, &data->lstart);
			data->currmds = data->currmds->next;
			i = k + 1;
		}
		k++;
	}
	if (!ms_fillnode(data, data->currmds->content, i, k))
		return (NULL);
	data->currmds->next = NULL;
	if (!ms_deqtfy_nodes(data, data->lstart))
		return (NULL);
	return ("Success");
}

/**
 * Fills node with adequate information from data->**currstr
 * first == first array for node
 * slast[superlast] == one after last array for node
 */
static char	*ms_fillnode(t_data *data, t_node *content, int first, int slast)
{
	int	size;

	size = ms_addsize(data, first, slast);
	content->cmd = malloc(size * sizeof(char *));
	if (!content->cmd)
		return (NULL);
	content->cmd[size - 1] = NULL;
	content->infd = NULL;
	content->outfd = NULL;
	content->status = 0;
	content->oper = 0;
	if (data->currstr[slast] && data->currstr[slast][0] == 60)
		content->oper = 1;
	if (data->currstr[slast] && data->currstr[slast][0] == 124)
		content->oper = 6;
	if (!ms_fillnodext(data, content, first, slast))
		return (NULL);
	return ("Success");
}

/**
 * Returns superlast - first + 1, -1 for each << in node, -2 for each <, >, >>
 */
static int	ms_addsize(t_data *data, int first, int superlast)
{
	int	size;

	size = superlast - first + 1;
	while (first < superlast)
	{
		if (data->currstr[first][0] == 60)
		{
			if (data->currstr[first][1] && data->currstr[first][1] == 60)
				size++;
			size -= 2;
		}
		if (data->currstr[first][0] == 62)
			size -= 2;
		first++;
	}
	return (size);
}

/**
 * More than 25 lines:
 * Fills node with adequate information from data->**currstr
 * i == first array for node/ aktuell
 * k == one after last array for node
 */
static char	*ms_fillnodext(t_data *data, t_node *content, int i, int k)
{
	int	c;

	c = 0;
	while (i < k)
	{
		if (data->currstr[i][0] == 60)
		{
			if (!data->currstr[i + 1])
				return (NULL);
			content->infd = ms_strdup(data->currstr[i + 1]);
			if (!content->infd)
				return (NULL);
			i += 2;
		}
		else if ((data->currstr[i]) && (data->currstr[i][0] == 62))
		{
			if (!data->currstr[i + 1])
				return (NULL);
			content->outfd = ms_strdup(data->currstr[i + 1]);
			if (!content->outfd)
				return (NULL);
			if (data->currstr[i][1] == 62)
				content->status = 1;
			i += 2;
		}
		else if ((data->currstr[i])
			&& (data->currstr[i][0] != 60) && (data->currstr[i][0] != 62))
		{
			content->cmd[c] = ms_strdup(data->currstr[i]);
			if (!content->cmd[c])
				return (NULL);
			i++;
			c++;
		}
	}
	return ("Success");
}
