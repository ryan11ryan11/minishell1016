/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:21:59 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:26:27 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_duplicate(char *name, t_envlist *envlist, char *arr, t_data *data)
{
	t_envlist	*tmp;
	char		**input;

	tmp = envlist;
	if (!name || !envlist)
		return (-1);
	while (tmp != NULL)
	{
		input = ft_split(tmp->value, '=');
		if (!input[0] || !input)
			return (0);
		if (ft_strlcmp_limited(input[0], name) == 0)
		{
			if (ft_strchr(arr, '=') != NULL)
			{
				free(tmp->value);
				tmp->value = ft_strdup(arr);
				data->errcode = 0;
			}
			doublearr_free(&input);
			return (-1);
		}
		doublearr_free(&input);
		tmp = tmp->next;
	}
	return (0);
}

char	*quo_add(char *arr)
{
	int		i;
	int		j;
	int		len;
	char	*new;

	len = ft_strlen(arr);
	i = 0;
	j = 0;
	new = (char *)malloc(sizeof(char) * (len + 3));
	while (i < len + 1)
	{
		new[i] = arr[j];
		if (ft_strchr(new, '"') == NULL && arr[j] == '=')
		{
			i ++ ;
			new[i] = '"';
		}
		i ++ ;
		j ++ ;
	}
	new[i] = '"';
	new[i + 1] = '\0';
	return (new);
}

void	print_all(t_envlist *envlist)
{
	t_envlist	*tmp;
	char		*new;

	tmp = envlist;
	while (tmp != NULL)
	{
		if (ft_strchr(tmp->value, '=') != NULL)
		{
			new = quo_add(tmp->value);
			ft_putstr_fd ("declare -x ", 1);
			ft_putstr_fd (new, 1);
			ft_putstr_fd ("\n", 1);
			tmp = tmp->next;
			free (new);
			continue ;
		}
		ft_putstr_fd ("declare -x ", 1);
		ft_putstr_fd (tmp->value, 1);
		ft_putstr_fd ("\n", 1);
		tmp = tmp->next;
	}
}

int	underbar_alphabet(char *msg, t_data *data)
{
	int	i;

	i = 0;
	while (msg[i] != '\0')
	{
		if (!((msg[0] >= 'A' && msg[0] <= 'Z') || \
		(msg[0] >= 'a' && msg[0] <= 'z')))
		{
			data->errcode = 1;
			ft_putstr_fd ("export: not a valid identifier\n", 2);
			return (-1);
		}
		if ((msg[i] >= 'A' && msg[i] <= 'Z') \
		|| (msg[i] >= 'a' && msg[i] <= 'z') \
		|| msg[i] == '_' || ((msg[i] >= '0' && msg[i] <= '9') || msg[i] == ' '))
			i ++ ;
		else
		{
			data->errcode = 1;
			ft_putstr_fd ("export: not a valid identifier\n", 2);
			return (-1);
		}
	}
	return (1);
}

int	is_empty(char *msg, t_data *data)
{
	if (msg == NULL || msg[0] == '\0')
	{
		ft_putstr_fd ("export: not a valid identifier\n", 2);
		data->errcode = 1;
		return (-1);
	}
	return (1);
}
