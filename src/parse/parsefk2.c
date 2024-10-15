/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:03:45 by jbober            #+#    #+#             */
/*   Updated: 2024/10/15 13:59:26 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_parsefk2_ctrl(t_data *data);
static char	*ms_remove_322(char *str, int i, int weakqt, int strongqt);
static void	ms_remove_322b(char *str, char *newstr, int *i, int *j);
static int	ms_remove_size(char *str, int weakqt, int strongqt);

/**
 * Control structure
 * Seperates >>, >, |, <, << (turning >outfile to > outfile)
 */
char	*ms_parsefk2_ctrl(t_data *data)
{
	data->currinput = ms_remove_322(data->currinput, 0, 0, 42);
	if (!data->currinput)
		return (NULL);
	data->currinput = ms_add_32(data->currinput, 0, 0, 42);
	return (data->currinput);
}

/**
 * Returns malloced copy of str without leading/trailing or double spaces
 * Frees given str
 * str = string to copy, i = 0, weakqt = 0, stronqt = 42
 */
static char	*ms_remove_322(char *str, int i, int weakqt, int strongqt)
{
	int		j;
	char	*newstr;

	j = 0;
	newstr = malloc(ms_remove_size(str, weakqt, strongqt) + 1);
	if (!newstr)
		return (NULL);
	while (str[i] && str[i] == 32)
		i++;
	while (str[i])
	{
		if (!ms_check_qt(str[i], &weakqt, &strongqt))
			ms_remove_322b(str, newstr, &i, &j);
		else
		{
			newstr[j] = str[i];
			j++;
			i++;
		}
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

/**
 * Copies str[i] only if it is not a double space
 * i++;
 * str = string to copy, newstr = string to copy to, i = &i, j = &j
 */
static void	ms_remove_322b(char *str, char *newstr, int *i, int *j)
{
	if (!(str[*i] == 32 && str[*i + 1] && str[*i + 1] == 32)
		&& !(str[*i] == 32 && !str[*i + 1]))
	{
		newstr[*j] = str[*i];
		(*j)++;
	}
	(*i)++;
}

/**
 * Returns the size of str without leading/trailing or double spaces
 * str = string to check, weakqt = 0, stronqt = 42
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
		if (!ms_check_qt(str[i], &weakqt, &strongqt))
		{
			if (!(str[i] == 32 && str[i + 1] && str[i + 1] == 32)
				&& !(str[i] == 32 && !str[i + 1]))
				j++;
			i++;
		}
		else
		{
			i++;
			j++;
		}
	}
	return (j);
}
