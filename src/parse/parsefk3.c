/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:36:57 by jbober            #+#    #+#             */
/*   Updated: 2024/08/30 12:57:46 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk3_ctrl(t_data *data);
static int	ms_countword(char *str, int numwords, int modus);
static char	*ms_add_item(t_data *data, char *str, int k);
static char	*ms_trimdup(char *str, int i);

/**
 * Control structure
 * Fills data->**currstr with each piece of data->*currinput
 */
char	*ms_parsefk3_ctrl(t_data *data)
{
	int	k;
	int	numwords;

	k = 0;
	numwords = ms_countword(data->currinput, 1, 0);
	data->currstr = malloc((numwords + 1) * sizeof(char *));
	if (!data->currstr)
		return (NULL);
	while (k < numwords)
	{
		if (!ms_add_item(data, data->currinput, k))
			return (NULL);
		k++;
	}
	data->currstr[k] = NULL;
}

/**
 * Modus 0: Counts the # of words in data->currstr
 * Modus 1: Returns the index of the first 32
 */
static int	ms_countword(char *str, int numwords, int modus)
{
	int	i;
	int	weakqt;
	int	strongqt;

	i = 0;
	weakqt = 0;
	strongqt = 42;
	while (str[i])
	{
		if ((str[i] == 34) && (strongqt % 2 == 0))
			weakqt++;
		if ((str[i] == 39) && (weakqt % 2 == 0))
			strongqt++;
		if ((str[i] == 32) && (weakqt % 2 == 0) && (strongqt % 2 == 0))
		{
			numwords++;
			if (modus == 1)
				return (i);
		}
		i++;
	}
	if (modus == 1)
		return (0);
	return (numwords);
}

/**
 * Mallocs and fills the kth word
 * Trims data->*currinput by the filled amount
 */
static char	*ms_add_item(t_data *data, char *str, int k)
{
	int	i;
	int	len;

	i = 0;
	len = ms_countword(str, 1, 1);
	data->currstr[k] = malloc((len + 1) * sizeof(char));
	if (!data->currstr[k])
		return (NULL);
	while (i < len)
	{
		data->currstr[k][i] = str[i];
		i++;
	}
	data->currstr[k][i] = '\0';
	str = ms_trimdup(str, len);
	return (str);
}

/**
 * Returns malloced cpy of str, excluding the first n chars + leading 32
 * Frees the provided str
 */
static char	*ms_trimdup(char *str, int i)
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
