/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:39:42 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/15 15:27:03 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t	*assign_pid(int num_args)
{
	pid_t	*new_pid;
	int		i;

	i = 0;
	new_pid = (pid_t *)malloc(sizeof(pid_t) * num_args);
	if (!new_pid)
		return (NULL);
	while (i < num_args)
	{
		new_pid[i] = -1;
		i ++ ;
	}
	return (new_pid);
}

char	*absolute_path(t_data *data)
{
	t_node	*argvt;
	
	argvt = data->lstart->content;
	if (access(argvt->cmd[0], X_OK) == 0)
		return ((char *)argvt->cmd[0]);
	return (NULL);
}

char	*pathfinder(char *command, t_data *data)
{
	char	*slashadded;
	char	*commandadded;
	int		i;
	char	*tmp;

	i = 0;
	if (!data->patharr || !command || !data->patharr)
		return (NULL);
	tmp = absolute_path(data);
	if (tmp != NULL)
		return (ft_strdup(tmp));
	while (data->patharr[i] != NULL)
	{
		slashadded = slashadd(data->patharr[i]);
		if (!slashadded)
			return (NULL);
		commandadded = commandadd(slashadded, command);
		free(slashadded);
		if (!commandadded || access(commandadded, X_OK) == 0)
			return (commandadded);
		free(commandadded);
		i ++ ;
	}
	return (NULL);
}

void	count_lstart(t_data *data)
{
	int	i;
	t_list	*tmp;

	tmp = data->lstart;
	i = 0;
	while (tmp)
	{
		i ++ ;
		tmp = tmp->next;
	}
	data->num_ndata = i;
}

void	doublearr_free(char ***arr)
{
	int	i;

	i = 0;
	if (arr == NULL || *arr == NULL)
		return ;
	while ((*arr)[i] != NULL)
	{
		free((*arr)[i]);
		i ++ ;
	}
	free (*arr);
	*arr = NULL;
}

char	*ft_get_env(t_data *data)
{
	t_envlist	*n_envlist;

	n_envlist = data->envlist;
	while(n_envlist)
	{
		if (n_envlist->value[0] == 'P' && n_envlist->value[1] == 'A' 
		&& n_envlist->value[2] == 'T' && n_envlist->value[3] == 'H' 
		&& n_envlist->value[4] == '=' && n_envlist->value[5] == '/')
			return (n_envlist->value);
		n_envlist = n_envlist->next;
	}
	return (NULL);
}

void	data_setting(t_data *data)
{
	char	*originalpath;
	char	*fullpath;

	originalpath = ft_get_env(data);
	if (!originalpath)
		data->patharr = NULL;
	else
	{
		fullpath = ft_strdup(originalpath);
		data->patharr = ft_split(fullpath, ':');
		free(fullpath);
	}
	data->num_pipe = count_pipe(data); // problem
	count_lstart(data);
	data->pid = assign_pid(data->num_ndata);
	data->pipe = assign_pipe(data->num_pipe);
	init_pipe(data);
}
