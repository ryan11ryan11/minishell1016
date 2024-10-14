/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:46:58 by jbober            #+#    #+#             */
/*   Updated: 2024/08/30 12:38:39 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Mallocs data->**currstr and fills each [k] with a word
 */
void	ms_currsplit(t_data *data)
{
	int	i;
	int	k;
	int	numwords;

	i = 0;
	k = 0;
	numwords = ms_countword(data, data->currinput);
	data->currstr = malloc((numwords + 1) * sizeof(char *));
	if (!data->currstr)
		ms_error(data, "parse/parsefk2.c 29: failloc :(", ENOMEM);
	while (k < numwords)
	{
		ms_currloc(data, k, &i);
		k++;
	}
	data->currstr[k] = NULL;
}

/**
 * Mallocs and fills the kth word
 */
void	ms_currloc(t_data *data, int k, int *i)
{
	int	j;
	int	len;

	j = 0;
	while (data->currinput[*i] && data->currinput[*i] == 32)
		(*i)++;
	len = ms_countchar(data, i);
	data->currstr[k] = malloc((len + 1) * sizeof(char));
	if (!data->currstr[k])
		ms_error(data, "parse/parsefk2.c 52: failloc :(", ENOMEM);
	data->currstr[k][len] = '\0';
	while (j < len)
	{
		data->currstr[k][j] = data->currinput[*i];
		(*i)++;
		j++;
	}
}
//asd test ficken

/**
 * Counts chars until 32
 */
int	ms_countchar(t_data *data, int *i)
{
	int	j;
	int	moda;
	int	modb;

	j = 0;
	moda = 0;
	modb = 0;
	while (data->currinput[*i + j])
	{
		if ((data->currinput[*i + j] == 34) && (modb == 0))
			moda++;
		if ((data->currinput[*i + j] == 39) && (moda == 0))
			modb++;
		if ((data->currinput[*i + j] == 32)
			&& (moda % 2 == 0) && (modb % 2 == 0))
			break ;
		j++;
	}
	return (j);
}

/**
 * Counts the # of words in data->currstr
 */
int	ms_countword(t_data *data, char *str)
{
	int	i;
	int	numwords;
	int	moda;
	int	modb;

	i = 0;
	numwords = 1;
	moda = 0;
	modb = 0;
	if (!str)
		ms_error(data, "parse/parsefk2.c 104: This error can not occur.	I would tell you details about it, but clearly I am not competent enough to do so. I am sorry to have disappointed you!", EINVAL);
	while (str[i])
	{
		if ((str[i] == 34) && (modb % 2 == 0))
			moda++;
		if ((str[i] == 39) && (moda % 2 == 0))
			modb++;
		if ((str[i] == 32) && (i != 0) && (str[i - 1] != 32)
			&& (moda % 2 == 0) && (modb % 2 == 0))
			numwords++;
		i++;
	}
	return (numwords);
}
