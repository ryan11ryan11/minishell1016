/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:01:51 by jbober            #+#    #+#             */
/*   Updated: 2024/08/21 14:46:38 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Checks data->currrinput and turns >outfile into > outfile
 * Works for >>, >, <<, <, |
 * Works only if >>> and <<< are impossible inputs, here's for hope
 */
void	ms_sepcmds(t_data *data, int i, int moda, int modb)
{
	int		j;
	int		numseps;
	char	*newstr;

	j = 0;
	numseps = ms_countseps(data->currinput, 0, 0);
	newstr = malloc((numseps + ms_strlen(data->currinput) + 1) * sizeof(char));
	if (!newstr)
		ms_error(data, "parse/parsefk1.c 30: failloc :(", ENOMEM);
	while (data->currinput[i])
	{
		if ((data->currinput[i] == 34) && (modb % 2 == 0))
			moda++;
		if ((data->currinput[i] == 39) && (moda % 2 == 0))
			modb++;
		if ((ms_checksep(data->currinput, i) == 1)
			&& (moda % 2 == 0) && (modb % 2 == 0))
		{
			newstr[i + j] = 32;
			j++;
		}
		newstr[i + j] = data->currinput[i];
		i++;
	}
	newstr[i + j] = '\0';
	ms_transep(data, newstr);
}

/**
 * Checks wether str[i] is <|> not followed by 32
 */
int	ms_checksep(char *str, int i)
{
	if ((str[i] == 60) && (str[i + 1] == 60))
		return (0);
	if ((str[i] == 60) && (str[i + 1] != 32) && (str[i + 1] != '\0'))
		return (1);
	if ((str[i] == 62) && (str[i + 1] == 62))
		return (0);
	if ((str[i] == 62) && (str[i + 1] != 32) && (str[i + 1] != '\0'))
		return (1);
	if ((str[i] == 124) && (str[i + 1] != 32) && (str[i + 1] != '\0'))
		return (1);
	return (0);
}

/**
 * Counts number of seperations needed
 */
int	ms_countseps(char *str, int moda, int modb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == 34) && (modb % 2 == 0))
			moda++;
		if ((str[i] == 39) && (moda % 2 == 0))
			modb++;
		if ((ms_checksep(str, i) == 1) && (moda % 2 == 0) && (modb % 2 == 0))
			j++;
		i++;
	}
	return (j);
}

/**
 * Transfers newstr into data->currinput
 */
void	ms_transep(t_data *data, char *newstr)
{
	int	i;

	i = 0;
	data->currinput = malloc((ms_strlen(newstr) + 1) * sizeof(char));
	if (!data->currinput)
		ms_error(data, "parse/parsefk1.c 101: failloc :(", ENOMEM);
	while (newstr[i])
	{
		data->currinput[i] = newstr[i];
		i++;
	}
	data->currinput[i] = '\0';
	free(newstr);
}
