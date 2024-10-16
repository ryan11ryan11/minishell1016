/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:43 by jbober            #+#    #+#             */
/*   Updated: 2024/10/16 17:19:33 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk2_ctrl(t_data *data);
static char	*ms_checkex(t_data *data, char *str, int weakqt, int strongqt);
static int	ms_get_lenterm(char *str, int l);
static char	*ms_get_value(t_data *data, char *str, int l, int lenterm);
static char	*ms_ex_strjoin(char *str1ng, char *str2ng, int l, int lenterm);
static char	*ms_removeterm(char *str1ng, char *freeme, int l, int lenterm);

/**
 * Control structure
 * Expands $*
 */
char	*ms_parsefk2_ctrl(t_data *data)
{
	char	*newstr;

	newstr = ms_strdup(data->currinput);
	if (!newstr)
		return (NULL);
	newstr = ms_checkex(data, data->currinput, 0, 42);
	if (!newstr)
		return (NULL);
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
		
		if ((ms_check_qt(str[i], &weakqt, &strongqt) < 2) && (str[i] == 36) && (str[i + 1] && str[i + 1] != 32 && str[i + 1] != 34))
		{
			if (str[i + 1] && str[i + 1] == 36)
			{
				i++;
				break;
			}
			lenterm = ms_get_lenterm(str, i);
			value = ms_get_value(data, str, i, lenterm);
			if (!value)
				return (NULL);
			if (!ms_strncmp("Hy7J$Lm3Pq1Rx4Vz8!@#^&*()_+{}|:<>?`~", value, 36))
				str = ms_removeterm(str, value, i, lenterm);
			else
				str = ms_ex_strjoin(str, value, i, lenterm);
			if (!str)
				return (NULL);
			i--;
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

	i = 1;
	if (str[l + 1] == 63)
		return (2);
	while (!(ms_cinset(str[l + i], " \t\n=:;|&'\"`(){}/$?*@\0", 1)))
		i++;
	return (i);
}

/**
 * Copies TERM in $TERM to lookme
 * Checks wether it finds TERM in env[k]
 * strdups lookme to the value of env[k]
 * Returns malloced *str which is VALUE in TERM=VALUE
 * lenterm == $TERM, while lookeme is "TERM", thus we don't need the usual +1
 * 		+2 though because we will put the output into ""
 *	str = str to ?, l = index to $ in $TERM, lenterm = strlen of $TERM
 */
static char	*ms_get_value(t_data *data, char *str, int l, int lenterm)
{
	int		i;
	int		k;
	char	*lookme;

	i = 0;
	if (str[l + 1] && str[l + 1] == 63)
	{
		lookme = ms_strdup(ms_itoa(g_lastexit));
		return (lookme);
	}
	lookme = malloc((lenterm + 2) * sizeof(char));
	if (!lookme)
		return (NULL);
	while ((str[i + l+ 1]) && (i + 1 < lenterm))
	{
		lookme[i] = str[i + l + 1];
		i++;
	}
	lookme[i] = '\0';
	k = ms_findexpanse(data, lookme);
	free(lookme);
	if (k == -1)
		return (ms_strdup("Hy7J$Lm3Pq1Rx4Vz8!@#^&*()_+{}|:<>?`~"));
	lookme = ms_strdup(data->env[k] + lenterm);
	return (lookme);
}

/**
 * Returns a malloced *str made out of str1ng til l,
 * 		str2ng, str1ng after (l + lenterm)
 * Also adds "" to the expansion
 * Frees str1ng and str2ng
 */
static char	*ms_ex_strjoin(char *str1ng, char *str2ng, int l, int lenterm)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(ms_strlen(str1ng) + ms_strlen(str2ng) - lenterm + 3);
	if (!newstr)
		return (NULL);
	while (i < l)
	{
		newstr[i] = str1ng[i];
		i++;
	}
	newstr[i] = 34;
	while ((i + j) < (l + ms_strlen(str2ng)))
	{
		newstr[1 + i + j] = str2ng[j];
		j++;
	}
	newstr[1 + i + j] = 34;
	while ((l + lenterm) < (ms_strlen(str1ng)))
	{
		newstr[2 + l + ms_strlen(str2ng)] = str1ng[l + lenterm];
		l++;
	}
	newstr[2 + l + ms_strlen(str2ng)] = '\0';
	free(str1ng);
	free(str2ng);
	return (newstr);
}

/**
 * Returns a malloced *str made out of str1ng removing the $TERM with $ at l
 * For $FAKE, lenterm = 5
 * Frees str1ng and freeme
 */

static char	*ms_removeterm(char *str1ng, char *freeme, int l, int lenterm)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	if (str1ng[l - 1] && str1ng[l - 1] == 32)
	{
		l--;
		lenterm++;
	}
	newstr = malloc(ms_strlen(str1ng) - lenterm + 1);
	if (!newstr)
		return (NULL);
	while (i < l)
	{
		newstr[i] = str1ng[i];
		i++;
	}
	while (i < (ms_strlen(str1ng) - lenterm))
	{
		newstr[i] = str1ng[i + lenterm];
		i++;
	}
	newstr[i] = '\0';
	free(str1ng);
	free(freeme);
	return (newstr);
}
