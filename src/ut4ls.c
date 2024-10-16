/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut4ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:40:44 by rakropp           #+#    #+#             */
/*   Updated: 2024/10/16 15:52:12 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_substrrev(char *str, int start, int len)
{
	int		c;
	char	*ret;

	c = 0;
	ret = malloc((len - start + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	while (str[start] && start <= len)
		ret[c++] = str[start++];
	ret[c] = '\0';
	return (ret);
}

static int	intlen(int n)
{
	int	ret;

	ret = 0;
	if (n == -2147483648)
		return (11);
	if (n == 0)
		return (1);
	if (n < 0)
	{
		ret++;
		n *= -1;
	}
	while (n)
	{
		n = n / 10;
		ret++;
	}
	return (ret);
}

char	*ms_itoa(int n)
{
	char	*ret;
	int		len;

	len = intlen(n);
	if (n == -2147483648)
		return (ms_strdup("-2147483648"));
	ret = malloc((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	if (n == 0)
		*ret = '0';
	if (n < 0)
	{
		n *= -1;
		*ret = '-';
	}
	ret[len--] = '\0';
	while (n)
	{
		ret[len--] = (n % 10) + 48;
		n = n / 10;
	}
	return (ret);
}

/**
 * Checks **env for *str
 * On Found, return k (as in env[k])
 * If not found, return -1
 */
int	ms_findexpanse(t_data *data, char *str)
{
	int	k;

	k = 0;
	while (data->env[k])
	{
		if (!ms_strncmp(data->env[k], str, ms_strlen(str)))
			return (k);
		k++;
	}
	return (-1);
}

/**
 * Mallocs + initializes the list of commands to data->**cstrl
 */
void	ms_ctrlitialize(t_data *data)
{
	data->cstrl = malloc(8 * sizeof(char *));
	if (!data->cstrl)
		ms_error(data, "parse/parse.c 32: failloc :(", ENOMEM);
	data->cstrl[7] = NULL;
	ms_ctrlfill(data, 0, "echo");
	ms_ctrlfill(data, 1, "cd");
	ms_ctrlfill(data, 2, "pwd");
	ms_ctrlfill(data, 3, "export");
	ms_ctrlfill(data, 4, "unset");
	ms_ctrlfill(data, 5, "env");
	ms_ctrlfill(data, 6, "exit");
}

/**
 * Mallocs and fills each data->*cstrl
 */
void	ms_ctrlfill(t_data *data, int k, char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ms_strlen(str);
	data->cstrl[k] = malloc((len + 1) * sizeof(char));
	if (!data->cstrl[k])
		ms_error(data, "parse/parse.c 55: failloc :(", ENOMEM);
	while (i < len)
	{
		data->cstrl[k][i] = str[i];
		i++;
	}
	data->cstrl[k][i] = '\0';
}

/**
 * Checks wether char c is contained in char *set
 * Modus 1 -> include '\0'
 * Returns 1 for yes, 0 for no
 */
int	ms_cinset(char c, char *set, int modus)
{
	int	i;

	i = 0;
	if (modus == 1)
	{
		if (!c)
			return (1);
	}
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
