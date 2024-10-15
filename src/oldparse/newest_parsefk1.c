/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:54:56 by jbober            #+#    #+#             */
/*   Updated: 2024/10/14 16:41:42 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ms_parsefk1_ctrl(t_data *data);
static char	*ms_remove_double32(char *str, int weakqt, int strongqt);
static int	ms_remove_size(char *str, int weakqt, int strongqt);
static char *ms_add_32(char *str, int weakqt, int strongqt);
static int	ms_add_size(char *str, int weakqt, int strongqt);

/**
 * Control structure
 * Seperates >>, >, |, <, << (turning >outfile to > outfile)
 */
char	*ms_parsefk1_ctrl(t_data *data)
{
	char	*newstr;

	data->currinput = ms_remove_double32(data->currinput, 0, 42);
	data->currinput = ms_radd_32(data->currinput, 0, 42);
	return (data->currinput);
}

/**
 * Removes double32 from str
 * Returns a malloced str
 * Frees given str
 */
static char	*ms_remove_double32(char *str, int weakqt, int strongqt)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(ms_strlen(str) + 1 - ms_remove_size(str, weakqt, strongqt));
	if (!newstr)
		returns (NULL);
	while (str[i] && str[i] == 32)
		i++;
	while (str[i])
	{
		if ((str[i] == 34) && !(strongqt % 2))
			weakqt++;
		if ((str[i] == 39) && !(weakqt % 2))
			strongqt++;
		while ((str[i] == 32) && (str[i + 1]) && (str[i + 1] == 32)
			&& !(weakqt % 2) && !(strongqt % 2))
			i++;
		if (str[i] == 32 && !str[i + 1])
			break ;
		newstr[j] = str[i + j];
		j++;
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

/**
 * Returns the size of str without double spaces
 */
static int	ms_remove_size(char *str, int weakqt, int strongqt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] == 32)
		i++;
	while (str[i])
	{
		if ((str[i] == 34) && !(strongqt % 2))
			weakqt++;
		if ((str[i] == 39) && !(weakqt % 2))
			strongqt++;
		if ((str[i] == 32) && (str[i + 1]) && ((str[i + 1] == 32) || (!str[i + j]))
			&& !(weakqt % 2) && !(strongqt % 2))
			j++;
		i++;
	}
	return (j);
}

/**
 * adds 32 before and after <, <<, |, >>, >
 * Returns a malloced char*
 * frees str*
 */
static char *ms_add_32(char *str, int weakqt, int strongqt)
{
	int		i;
	char	*newstr;

	i = 0;
}

/**
 * Returns the size of str with added spaces
 */
static int	ms_add_size(char *str, int weakqt, int strongqt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == 34) && !(strongqt % 2))
			weakqt++;
		if ((str[i] == 39) && !(weakqt % 2))
			strongqt++;
		if (!(weakqt % 2) && !(strongqt % 2))
		{
			if ((str[i] != 32) && ((str[i + 1] == 60)
				|| (str[i + 1] == 62) || (str[i + 1] == 124)))
				j++;
			if (!(j % 2) && str[i] == 60)// aaaaaa
		}
		i++;
	}
}
