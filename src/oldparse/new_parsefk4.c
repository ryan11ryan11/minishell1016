/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:24:55 by jbober            #+#    #+#             */
/*   Updated: 2024/10/14 14:32:22 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk4_ctrl(t_data *data);
static char	*ms_fillnode(t_data *data, t_node *content, int i, int k);
static char	*ms_fillnodext(t_data *data, t_node *content, int i, int k);
static char	*ms_cp_to_lst(t_data *data, t_node *content, int k, int c);

/**
 * Control structure
 * Creates list with content of data->*currinput
 * Pipe -> new node
 */
char	*ms_parsefk4_ctrl(t_data *data)
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
	data->currmds = data->currmds->next;
	data->currmds = NULL;
	return ("Success");
}

/**
 * Fills node with adequate information from data->**currstr
 * i == first array for node
 * k == one after last array for node
 */
static char	*ms_fillnode(t_data *data, t_node *content, int i, int k)
{
	content->cmd = malloc(((k - i) + 1) * sizeof(char *));//if < or >, will malloc too much
	if (!content->cmd)
		return (NULL);
	content->path = NULL;//missing
	content->infd = 0;
	content->outfd = 1;
	if (data->currstr[k] && data->currstr[k][0] == 124)//new
		content->oper = 6;
	else
		content->oper = 0;
	if (!ms_fillnodext(data, content, i, k))
		return (NULL);
	return ("Success");
}

/**
 * More than 25 lines:
 * Fills node with adequate information from data->**currstr
 * i == first array for node
 * k == one after last array for node
 */
static char	*ms_fillnodext(t_data *data, t_node *content, int i, int k)
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
			i++;
		else
		{
			if (!ms_cp_to_lst(data, content, i, c))
				return (NULL);
			c++;
		}
		i++;
	}
	content->cmd[i] = NULL;
	return ("Success");
}

/**
 * Copies content of **currstr[k] to node
 */
static char	*ms_cp_to_lst(t_data *data, t_node *content, int k, int c)
{
	int	i;

	i = 0;
	content->cmd[c] = malloc((ms_strlen(data->currstr[k] + 1) * sizeof(char)));
	if (!content->cmd[c])
		return (NULL);
	while (data->currstr[k][i])
	{
		content->cmd[c][i] = data->currstr[k][i];
		i++;
	}
	content->cmd[c][i] = '\0';
	return ("Success");
}
