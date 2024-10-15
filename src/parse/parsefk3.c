/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:08:59 by jbober            #+#    #+#             */
/*   Updated: 2024/10/15 12:09:12 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk3_ctrl(t_data *data);
static int	ms_getnumwords(char *str);
static int	ms_fillcurrstr(t_data *data, int numwords);
static int	ms_additem(t_data *data, int k, int start);
static int	ms_partlen(t_data *data, int start);

/**
 * Control structure
 * Fills data->**currstr with each piece of data->*currinput
 */
char	*ms_parsefk3_ctrl(t_data *data)
{
	int	numwords;

	numwords = ms_getnumwords(data->currinput);
	data->currstr = malloc((numwords + 1) * sizeof(char *));
	if (!data->currstr)
		return (NULL);
	if (!ms_fillcurrstr(data, numwords))
		return (NULL);
	return ("Success");
}

/**
 * Returns the number of words (strings seperated by 32)
 */
static int	ms_getnumwords(char *str)
{
	int	i;
	int	numwords;
	int	weakqt;
	int	strongqt;

	i = 0;
	numwords = 1;
	weakqt = 0;
	strongqt = 42;
	while (str[i])
	{
		if ((str[i] == 34) && (strongqt % 2 == 0))
			weakqt++;
		if ((str[i] == 39) && (weakqt % 2 == 0))
			strongqt++;
		if ((str[i] == 32) && (weakqt % 2 == 0) && (strongqt % 2 == 0))
			numwords++;
		i++;
	}
	return (numwords);
}

/**
 * Fills the array data->**currstr with content from data->*currinput
 * Returns 0 on malloc fail
 */
static int	ms_fillcurrstr(t_data *data, int numwords)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	data->currstr[numwords] = NULL;
	while (k < numwords)
	{
		i = ms_additem(data, k, i);
		if (!i)
			return (0);
		k++;
	}
	return (1);
}

/**
 * Adds the 32-delimited-str in data->*currinput to data->*currstr[k]
 * Returns 0 on malloc fail
 * start == first letter of str in *currinput
 */
static int	ms_additem(t_data *data, int k, int start)
{
	int	i;
	int	j;
	int	len;

	len = (ms_partlen(data, start) - start);
	i = 0;
	j = start;
	data->currstr[k] = malloc((len + 1) * sizeof(char));
	if (!data->currstr[k])
		return (0);
	data->currstr[k][len] = '\0';
	while (i < len)
	{
		data->currstr[k][i] = data->currinput[j];
		i++;
		j++;
	}
	return (len + start + 1);
}

/**
 * Returns the index of the next 32/'\0' in data->*currinput
 * start == first letter of str in *currinput
 */
static int	ms_partlen(t_data *data, int start)
{
	int	i;
	int	weakqt;
	int	strongqt;

	i = start;
	weakqt = 0;
	strongqt = 42;
	while (data->currinput[i])
	{
		if ((data->currinput[i] == 34) && (strongqt % 2 == 0))
			weakqt++;
		if ((data->currinput[i] == 39) && (weakqt % 2 == 0))
			strongqt++;
		if ((data->currinput[i] == 32) && (weakqt % 2 == 0)
			&& (strongqt % 2 == 0))
			return (i);
		i++;
	}
	return (i);
}
