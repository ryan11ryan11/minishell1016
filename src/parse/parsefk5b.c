/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsefk5b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:39:34 by jbober            #+#    #+#             */
/*   Updated: 2024/10/16 16:58:43 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*ms_deqtfy_nodes(t_data *data, t_list *iamhere);
static char	*ms_cleanqt(char *str, int weakqt, int strongqt);
static int	ms_skipqt(char *str, int i, int *weakqt, int *strongqt);
static int	ms_countqt(char *str, int weakqt, int strongqt);

/**
 * Goes through each cmd in each node and removes quotes
 * iamhere -> data->lstart or data->lstart->next
 */
char	*ms_deqtfy_nodes(t_data *data, t_list *iamhere)
{
	int	k;

	k = 0;
	if (!iamhere)
		return ("End of List");
	while (iamhere->content->cmd[k])
	{
		printf("---\t old-cmd[%i] == !%s!\n", k, iamhere->content->cmd[k]);
		iamhere->content->cmd[k] = ms_cleanqt(iamhere->content->cmd[k], 0, 42);
		if (!iamhere->content->cmd[k])
			return (NULL);
		printf("---\t new-cmd[%i] == !%s!\n", k, iamhere->content->cmd[k]);
		k++;
	}
	if (!ms_deqtfy_nodes(data, iamhere->next))
		return (NULL);
	return ("Success");
}

/**
 * Returns a copy of str without unwanted qts
 * Frees str
 * str = str to handle, weakqt = 0, strongqt = 42
 */
static char	*ms_cleanqt(char *str, int weakqt, int strongqt)
{
	int		i;
	int		oldi;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	newstr = malloc(ms_strlen(str) + 1 - ms_countqt(str, 0, 42));
	if (!newstr)
		return (NULL);
	while (str[i + j])
	{
		oldi = i;
		i += ms_skipqt(str, (i + j), &weakqt, &strongqt);
		if (i == oldi)
		{
			newstr[j] = str[i + j];
			j++;
		}
	}
	newstr[j] = '\0';
	free(str);
	return (newstr);
}

/**
 * Increses i if a char needs to be skipped on account of being a qt
 * Returns number of chars skipped
 * str, i == str[i] to be examined, weakqt == 0, stronqt == 42
 */
static int	ms_skipqt(char *str, int i, int *weakqt, int *strongqt)
{
	int	qt;

	qt = ms_check_qt(str[i], weakqt, strongqt);
	if ((!qt) && (str[i] == 34 || str[i] == 39))
		return (1);
	if ((qt == 1) && (str[i] == 34))
		return (1);
	if ((qt == 2) && (str[i] == 39))
		return (1);
	return (0);
}

/**
 * Returns number of chars to be removed by qt-cleansing
 * str == str to be cleansed, weakqt == 0, stronqt == 42
 */
static int	ms_countqt(char *str, int weakqt, int strongqt)
{
	int	i;
	int	j;
	int	qt;

	i = 0;
	j = 0;
	while (str[i])
	{
		qt = ms_check_qt(str[i], &weakqt, &strongqt);
		if ((!qt) && (str[i] == 34 || str[i] == 39))
			j++;
		if ((qt == 1) && (str[i] == 34))
			j++;
		if ((qt == 2) && (str[i] == 39))
			j++;
		i++;
	}
	return (j);
}

