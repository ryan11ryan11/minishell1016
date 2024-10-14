/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:43 by jbober            #+#    #+#             */
/*   Updated: 2024/10/14 10:42:02 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk2_ctrl(t_data *data);
static char	*ms_checkex(t_data *data, char *str, int weakqt, int strongqt);
static int	ms_get_lenterm(char *str, int l);
static char	*ms_get_value(t_data *data, char *str, int l, int lenterm);
static char	*ms_ex_strjoin(char *str1ng, char *str2ng, int l, int lenterm);

/**
 * Control structure
 * Expands $*
 */
char	*ms_parsefk2_ctrl(t_data *data)
{
	char	*newstr;

	newstr = ms_checkex(data, data->currinput, 0, 42);
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
 * Checks str for $, expands them
 * Returns malloced str
 */
static char	*ms_checkex(t_data *data, char *str, int weakqt, int strongqt)
{
	int		i;
	int		lenterm;
	char	*value;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 34) && !(strongqt % 2))
			weakqt++;
		if ((str[i] == 39) && !(weakqt % 2))
			strongqt++;
		if (str[i] == 36)
		{
			lenterm = ms_get_lenterm(str, i);
			value = ms_get_value(data, str, i, lenterm);
			if (!value)
				return (NULL);
			str = ms_ex_strjoin(str, value, i, lenterm);
			if (!str)
				return (NULL);
		}
		i++;
	}
	return (str);
}

/**
 * Returns len of $TERM in TERM=VALUE
 * str[l] == $
 */
static int	ms_get_lenterm(char *str, int l)
{
	int	i;

	i = 0;
	if (str[l + 1] == 63)
		return (2);
	while (!(ms_cinset(str[l + i], " \t\n=:;|&'\"`(){}/$?*@", 1)))
		i++;
	return (i);
}

/**
 * Returns malloced *str which is VALUE in TERM=VALUE
 * str[l] == $
 * lenterm == $TERM, while lookeme is "TERM", thus we don't need the usual +1
 */
static char	*ms_get_value(t_data *data, char *str, int l, int lenterm)
{
	int		i;
	int		k;
	char	*lookme;

	i = 1;
	if (str[l + 1] == 63)
		return (ms_itoa(g_lastexit));
	lookme = malloc((lenterm) * sizeof(char));
	if (!lookme)
		return (NULL);
	while (str[l + i])
	{
		lookme[i - 1] = str[l + 1];
		i++;
	}
	lookme[i - 1] = '\0';
	k = ms_findexpanse(data, lookme);
	free(lookme);
	if (k == -1)
		return (NULL);
	lookme = ms_strdup(data->env[k] + lenterm);
	return (lookme);
}

/**
 * Returns a malloced *str made out of str1ng til l,
 * 		str2ng, str1ng after (l + lenterm)
 * Frees str1ng and str2ng
 */
static char	*ms_ex_strjoin(char *str1ng, char *str2ng, int l, int lenterm)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(ms_strlen(str1ng) + ms_strlen(str2ng) - lenterm + 1);
	if (!newstr)
		return (NULL);
	while (i < l)
	{
		newstr[i] = str1ng[i];
		i++;
	}
	while ((i + j) < (l + ms_strlen(str2ng)))
	{
		newstr[i + j] = str2ng[j];
		j++;
	}
	while ((l + lenterm) < (ms_strlen(str1ng)))
	{
		newstr[l + ms_strlen(str2ng)] = str1ng[l + lenterm];
		l++;
	}
	newstr[l + ms_strlen(str2ng)] = '\0';
	free(str1ng);
	free(str2ng);
	return (newstr);
}
