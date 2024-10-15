/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:35:18 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/15 14:27:45 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_envplist(t_data *data)
{
	int			i;
	t_envlist	*tmp;

	tmp = data->envlist;
	i = 0;
	while (tmp != NULL)
	{
		i ++ ;
		tmp = tmp->next;
	}
	return (i);
}

int	envp_setting(t_data *data)
{
	if (data->new_envp != NULL)
	{
		doublearr_free(&data->new_envp);
		data->new_envp = NULL;
	}
	data->num_envp = count_envplist(data);
	data->new_envp = (char **)malloc(sizeof(char *) * (data->num_envp + 1));
	data->new_envp[data->num_envp] = NULL;
	if (!data->new_envp)
	{
		perror("envp error");
		return (-1);
	}
	return (1);
}

void	envp_maker(t_data *data)
{
	int			i;
	t_envlist	*tmp;

	i = 0;
	if (envp_setting(data) == -1) // problem
		return ;
	if (data->env != NULL)
		tmp = data->envlist;
	while (i < data->num_envp)
	{
		data->new_envp[i] = ft_strdup(tmp->value);
		if (!data->new_envp[i])
		{
			doublearr_free(&data->new_envp);
			return ;
		}
		i ++ ;
		tmp = tmp->next;
	}
}

char	*slashadd(char *path)
{
	char	*new;
	int		i;

	i = 0;
	while (path[i])
		i ++ ;
	new = (char *)malloc(sizeof(char) * (i + 2));
	if (!new)
		return (NULL);
	ft_strlcpy(new, path, i + 1);
	new[i] = '/';
	new[i + 1] = '\0';
	return (new);
}

char	*commandadd(char *slashadded, char *command)
{
	int		len_slashadded;
	int		len_command;
	char	*result;

	len_slashadded = ft_strlen(slashadded);
	len_command = ft_strlen(command);
	result = (char *)malloc((len_slashadded + len_command + 1) * sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, slashadded, len_slashadded + 1);
	ft_strlcpy(result + len_slashadded, command, len_command + 1);
	result[len_slashadded + len_command] = '\0';
	return (result);
}
