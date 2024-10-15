/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:23:27 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:15:05 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	name_check(char *arr, t_envlist *envlist, t_data *data)
{
	char	**input;

	input = ft_split(arr, '=');
	if (!input)
		return (-1);
	if (underbar_alphabet(input[0], data) == -1 || is_empty(input[0], data) == -1 || \
	is_alphabet(arr, data) == 1 || is_duplicate(input[0], envlist, arr, data) == -1)
	{
		doublearr_free(&input);
		return (-1);
	}
	doublearr_free(&input);
	return (1);
}

void	ft_envlist_back(t_envlist **lst, t_envlist *new)
{
	t_envlist	*last;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	new->next = NULL;
}

int	add_newblock(t_envlist **envlist, char *content, t_data *data)
{
	t_envlist	*new;

	new = (t_envlist *)malloc(sizeof(t_envlist));
	if (!new)
	{
		perror("malloc allocation failed");
		return (-1);
	}
	new->value = ft_strdup(content);
	ft_envlist_back(envlist, new);
	data->errcode = 0;
	return (1);
}

int	add_truespace(char *line, int *i, int *num_truespace)
{
	if (line[*i] && line[*i] == ' ')
	{
		while (line[*i] == ' ' && line[*i] != '\0')
			(*i)++;
		if (line[*i] != '\0')
			(*num_truespace)++;
	}
	return (0);
}

int	newarr_counter(char *line)
{
	int	i;
	int	num_truespace;

	num_truespace = 0;
	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i ++ ;
	while (line[i])
	{
		add_truespace(line, &i, &num_truespace);
		if (line[i] == '"' || line[i] == '\'')
		{
			i ++ ;
			while ((line[i] != '"' && line[i] != '\'') && line[i] != '\0')
				i ++ ;
		}
		if (line[i])
			i ++ ;
	}
	return (num_truespace);
}
