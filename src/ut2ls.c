/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut2ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:46:15 by jbober            #+#    #+#             */
/*   Updated: 2024/10/15 13:45:28 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks wether char *str is equal to char *x of char **lst
 * returns 0 for no, 1 for yes
 */
int	ms_strinlst(t_data *data, char *str)
{
	int	k;

	k = 0;
	while (data->cstrl[k])
	{
		if (ms_strncmp(data->cstrl[k], str, ms_strlen(str)) == 0)
			return (1);
		k++;
	}
	return (0);
}

/**
 * Checks wether chars *set and *str are the same
 * Returns 0 if yes, something else if no
*/
int	ms_strncmp(char	*set, char *str, int len)
{
	int	i;

	i = 0;
	if (!len)
		return (0);
	while (set[i] && str[i] && i < len)
	{
		if (set[i] != str[i])
			return ((unsigned char)set[i] - (unsigned char)str[i]);
		i++;
	}
	if (i == len)
		i--;
	return ((unsigned char)set[i] - (unsigned char)str[i]);
}

/**
 * Checks wether char *str is contained in char *bigstr
 * Returns 0 for no, 1 for yes
 */
int	ms_strcontains(char *str, char *bigstr)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0);
	while (bigstr[i])
	{
		j = 0;
		while (bigstr[i + j] == str[j])
		{
			j++;
			if (!str[j])
				return (1);
		}
		i++;
	}
	return (0);
}

/**
 * Mallocs and returns pointer to copy of str
 * Does not free str
 * Returns NULL on failloc
 */
char	*ms_strdup(char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = malloc((ms_strlen(str) + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

/**
 * Mallocs and returns bigstr, which is str1ng + str2ng
 * Does not free str1ng + str2ng
 */
char	*ms_strjoin(char *str1ng, char *str2ng)
{
	int		i;
	int		j;
	char	*bigstr;
	
	i = 0;
	j = 0;
	bigstr = malloc((ms_strlen(str1ng) + ms_strlen(str2ng) + 1) * sizeof(char));
	if (!bigstr)
		return (NULL);
	while (str1ng[i])
	{
		bigstr[i] = str1ng[i];
		i++;
	}
	while (str2ng[j])
	{
		bigstr[i + j] = str2ng[j];
		j++;
	}
	bigstr[i + j] = '\0';
	return (bigstr);
}
