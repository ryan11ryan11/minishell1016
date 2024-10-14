/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:46 by jbober            #+#    #+#             */
/*   Updated: 2024/08/30 12:33:47 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk3_ctrl(t_data *data);
static int	ms_clean_node(t_data *data, t_node *node, char *str, int k);
static int	ms_fillnode(t_data *data, t_node *content, int k);
static char	*ms_filldup(char *str, int i);
static int	ms_fillnode_len(char *str, int modus);

/**
 * Creates list with content of data->*currinput
 * Pipe -> new node
 * node->cmd[k] delimited by 32
 */
char	*ms_parsefk3_ctrl(t_data *data)
{
	int	k;

	k = 0;
	data->currmds = ms_lstnew(data);
	data->lstart = data->currmds;
	while (k != -2)
	{
		k = ms_clean_node(data, data->currmds->content, data->currinput, k);
		k = ms_fillnode(data, data->currmds->content, k);// return k + 1 on Success, 0 on Error, -1 on |, -2 on finish
		if (k == 0)
			return (NULL);
		if (k == -1)
		{
			ms_lstadd_back(data, &data->lstart);
			data->currmds = data->currmds->next;
			k = 0;
		}
	}
	data->currmds = data->currmds->next;
	data->currmds = NULL;
	// Verteiler geht alle cmd[k] durch und
	/*
	
	else
		copy to list
		c++;
	k++;
	*/
	// PATH!
	// Initialize infd = 0, outfd = 1, PATH = NULL jedes Node
	// Contentcopy nur wenn nicht ><
	return ("Success");
}

/**
 * Checks wether the next cmd[k] would be <, >, >>
 */
static int	ms_clean_node(t_data *data, t_node *content, char *str, int k)
{
	int	i;

	i = 0;
	if (!str)
		return (-2);
	if (k == 0)
	{
		content->infd = 0;
		content->outfd = 1;
		content->path = NULL;
	}
	if ((str[i] == 60) && (str[i + 1] == 32))
	{
		content->infd = open(cmd[k + 1], O_RDONLY);
		if (content->infd < 0)
			ms_error(data, "FILE/LINE", ENOENT);
		i++;
	}
	if (str[i] == 62)
	{
		content->outfd = open(cmd[k + 1], O_RDWR | O_CREAT, 0777);
		if (content->outfd < 0)
			ms_error(data, "FILE/LINE", ENOENT);
		i++;
		if (str[i + 1] == 62)
			i++;
	}
	if (i > 0)
		ms_filldup(str, i);
	return (k);
}

/**
 * Fills content->*cmds[k] with first word of data->*currinput
 * Replaces data->*currinput with the same minus first word
 */
static int	ms_fillnode(t_data *data, t_node *content, int k) // at some point norminette for parsefk3b.c
{
	int		i;
	int		len;

	// need to do infd, outfd, path!
	i = 0;
	if (!data->currinput)
		return (-2);
	if (data->currinput[i] == 124)
	{
		data->currinput = ms_filldup(data->currinput, 2);
		if (!data->currinput)
			return (0);
		return (-1);
	}
	if (k == 0)
	{
		len = ms_fillnode_len(data->currinput, 1);
		content->cmd = malloc((len + 1) * sizeof(char *));
		if (!content->cmd)
			return (0);
		content->cmd[len] = NULL;
	}
	len = ms_fillnode_len(data->currinput, 0);
	content->cmd[k] = malloc((len + 1));
	if (!content->cmd[k])
		return (0);
	while (i < len)
	{
		content->cmd[k][i] = data->currinput[i];
		i++;
	}
	content->cmd[k][i] = '\0';
	data->currinput = ms_filldup(data->currinput, len);
	if (!data->currinput)
		return (0);
	return (k + 1);
}

/**
 * Returns malloced cpy of str, excluding the first n chars + leading 32
 * Frees the provided str
 */
static char	*ms_filldup(char *str, int i)
{
	int		j;
	char	*newstr;

	j = 0;
	while (str[i] == 32)
		i++;
	if (!str[i])
		return (NULL);
	newstr = malloc((ms_strlen(str) - i + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (str[i + j])
	{
		newstr[j] = str[i + j];
		j++;
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

/**
 * Modus 0 -> returns first occurence of 32 outside of "'
 * Modus 1 -> returns number of occurences of 32 outside of "'
 */
static int	ms_fillnode_len(char *str, int modus)
{
	int	i;
	int	num32;
	int	weakqt;
	int	strongqt;

	i = 0;
	num32 = 0;
	weakqt = 0;
	strongqt = 42;
	while (str[i])
	{
		if ((str[i] == 34) && !(strongqt % 2))
			weakqt++;
		if ((str[i] == 39) && !(weakqt % 2))
			strongqt++;
		if ((str == 32) && !(weakqt % 2) && !(strongqt % 2))
		{
			if (modus == 0)
				return (i);
			num32++;
		}
		i++;
	}
	if (!str[i])
		return (0);
	return (num32);
}
