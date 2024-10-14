/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:40 by jbober            #+#    #+#             */
/*   Updated: 2024/10/14 10:37:38 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk1_ctrl(t_data *data);
static char	*ms_remove_double32(char *str);
static int	ms_countseps(char *str);
static int	ms_checkseps(char *str, int i);
static char	*ms_placeseps(char *str, int numseps, int weakqt, int strongqt);

/**
 * Control structure
 * Seperates >>, >, |, <, << (turning >outfile to > outfile)
 */
char	*ms_parsefk1_ctrl(t_data *data)
{
	int		numseps;
	char	*newstr;

	data->currinput = ms_remove_double32(data->currinput);
	if (!data->currinput)
		return (NULL);
	numseps = ms_countseps(data->currinput);
	newstr = ms_placeseps(data->currinput, numseps, 0, 42);
	if (!newstr)
		return (NULL);
	free(data->currinput);
	data->currinput = ms_strdup(newstr);
	free(newstr);
	if (!data->currinput)
		return (NULL);
	return (data->currinput);
}

/**
 * Removes any multiple 32
 * frees(str)
 */
static char	*ms_remove_double32(char *str)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc((ms_strlen(str) - ms_count32(str) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (str[i + j])
	{
		if ((str[i + j] == 32) && (((str[i + j + 1] == 32) || !(str[i + j + 1]))
			|| !(i + j)))
			j++;
		else
		{
			newstr[i] = str[i + j];
			i++;
		}
	}
	newstr[i] = '\0';
	free(str);
	return (newstr);
}

/**
 * Returns the number of seperator needed to seperate all >>, >, |, <, <<
 */
static int	ms_countseps(char *str)
{
	int	i;
	int	j;
	int	weakqt;
	int	strongqt;

	i = 0;
	j = 0;
	weakqt = 0;
	strongqt = 42;
	while (str[i])
	{
		if ((str[i] == 34) && !(strongqt % 2))
			weakqt++;
		if ((str[i] == 39) && !(weakqt % 2))
			strongqt++;
		if ((ms_checkseps(str, i)) && !(weakqt % 2) && !(strongqt % 2))
			j++;
		i++;
	}
	return (j);
}

/**
 * Checks wether str[i] should contain a 32
 * 	- because it is followed by >>, >, |, <, <<
 *  - because it follows >>, >, |, <, <<
 * Returns 1 for yes, 0 for no
 */
static int	ms_checkseps(char *str, int i)
{
	if ((str[i] == 60) && !(ms_cinset(str[i + 1], "< ", 1)))
		return (1);
	if ((str[i] == 62) && !(ms_cinset(str[i + 1], "> ", 1)))
		return (1);
	if ((str[i] == 124) && !(ms_cinset(str[i + 1], " ", 1)))
		return (1);
	if (!(ms_cinset(str[i], " <|>", 0)) && (ms_cinset (str[i + 1], "<|>", 0)))
		return (1);
	return (0);
}

/**
 * Seperates all >>, >, |, <, << in *str
 * Returns a malloced *str
 */
static char	*ms_placeseps(char *str, int numseps, int weakqt, int strongqt)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc((ms_strlen(str) + numseps + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == 34) && !(strongqt % 2))
			weakqt++;
		if ((str[i] == 39) && !(weakqt % 2))
			strongqt++;
		if ((ms_checkseps(str, i)) && !(weakqt) && !(strongqt))
		{
			newstr[i + j] = 32;
			j++;
		}
		newstr[i + j] = str[i];
		i++;
	}
	return (newstr);
}
