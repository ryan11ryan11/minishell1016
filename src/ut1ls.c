/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut1ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:03:12 by jbober            #+#    #+#             */
/*   Updated: 2024/08/21 14:48:13 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// what the fuck is happening??? it is not working and counting way to much?????

/**
 * Mallocs and returns array of str delimited by char split
 * Does not free the original str
 */
char	**ms_split(t_data *data, char *str, char split)
{
	int		k;
	int		*sep;
	char	**bigstr;

	k = 0;
	sep = ms_countsplit(data, str, split);
	bigstr = malloc((sep[0] + 1 + 1) * sizeof(char *));
	if (!bigstr)
		ms_error(data, "ut1ls.c 31: failloc :(", ENOMEM);
	while (k < sep[0] + 1)
	{
		bigstr[k] = ms_substr(data, str, sep[k + 1], sep[k + 2]);
		k++;
	}
	bigstr[k] = NULL;
	free(sep);
	return (bigstr);
}

// sep[0] == 11 when there is just one word

/**
 * Returns an int *sep
 * 	sep[0] == number of seperators
 * 	sep[1] == 0;
 * 	sep[k] == position of seperator/ last char
 */
int	*ms_countsplit(t_data *data, char *str, char split)
{
	int	i;
	int	k;
	int	*sep;

	i = 0;
	sep = malloc((ms_sepcount(str, split) + 3) * sizeof(int));
	if (!sep)
		ms_error(data, "ut1ls.c 59: failloc :(", ENOMEM);
	k = 2;
	sep[0] = 0;
	sep[1] = 0;
	while (str[i])
	{
		if (str[i] == split)
		{
			sep[0]++;
			sep[k++] = i;
		}
		i++;
	}
	sep[k] = i;
	return (sep);
}

/**
 * Returns the number of seperators in str
 */
int	ms_sepcount(char *str, char split)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == split)
			count++;
		i++;
	}
	return (count);
}

/**
 * Mallocs and returns *newstr, which contains everything between str[i] - str[j]
 */
char	*ms_substr(t_data *data, char *str, int i, int j)
{
	int		k;
	char	*newstr;

	k = 0;
	if (!(j > i))
		return (NULL);
	if (i == 0)
		newstr = malloc((j - i + 1) * sizeof(char)); // why minus 0?
	else
		newstr = malloc((j - i) * sizeof(char)); // plus 1??
	if (!newstr)
		ms_error(data, "ut1ls.c 111: failloc :(", ENOMEM);
	if (i != 0)
		i++; // why i++?
	while ((i < j) && (str[i]))
	{
		newstr[k++] = str[i++]; // endless loop
	}
	newstr[k] = '\0';
	return (newstr);
}

/**
 * Mallocs and returns the str beginning at the last slash
 * Frees the original str
*/
char	*ms_speciasplit(t_data *data, char *str)
{
	char	*newstr;
	int		i;
	int		j;

	i = ms_strlen(str) - 1;
	j = 0;
	while (str[i] && str[i] != 47)
		i--;
	newstr = malloc((ms_strlen(str) - i + 1) * sizeof(char));
	if (!newstr)
	{
		free(str);
		ms_error(data, "ut1ls.c 140: failloc :(", ENOMEM);
	}
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free (str);
	return (newstr);
}
