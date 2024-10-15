/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:24:30 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:15:08 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**new_arr_init(char *line)
{
	char	**new_arr;
	int		num_newarr;
	int		i;

	i = 0;
	num_newarr = newarr_counter(line);
	new_arr = (char **)malloc(sizeof(char *) * (num_newarr + 2));
	while (i < num_newarr + 2)
	{
		new_arr[i] = NULL;
		i ++ ;
	}
	return (new_arr);
}

char	*make_arr(char *line, int i, int j)
{
	char	*new;

	if (!line || i < 1)
		return (NULL);
	new = (char *)malloc(sizeof(char) * (i - j + 1));
	ft_strncpy(new, line + j, i - j);
	return (new);
}

int	quo_jump(int *i, int *j, char *line)
{
	if (*i == 0 && line[*i] == ' ')
	{
		while (line[*i] && line[*i] == ' ')
		{
			(*j)++;
			(*i)++;
		}
	}
	if (line[*i] == '"' || line[*i] == '\'')
	{
		(*i)++;
		while ((line[*i] != '"' && line[*i] != '\'') && line[*i] != '\0')
			(*i)++;
	}
	return (1);
}

void	new_add(int *i, int *j, char *line, char **new_arr)
{
	char	*new;

	if (line[*i] == ' ')
	{
		new = make_arr(line, *i, *j);
		add_arr(new_arr, new);
		free (new);
		while (line[*i + 1] == ' ' && line[*i + 1] != '\0')
			(*i)++;
		*j = *i + 1;
	}
}

char	**new_arr_maker(char *line)
{
	char	**new_arr;
	char	*new;
	int		i;
	int		j;

	j = 0;
	i = 0;
	new_arr = new_arr_init(line);
	while (line[i])
	{
		quo_jump(&i, &j, line);
		new_add(&i, &j, line, new_arr);
		i ++ ;
	}
	if (i != j)
	{
		new = make_arr(line, i, j);
		add_arr(new_arr, new);
		free (new);
	}
	return (new_arr);
}
