/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:26:03 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 19:04:34 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_component_check(t_data *data)
{
	t_list	*tmp;
	t_node	*argvt;
	char	*command;
	char	*path;

	tmp = data->currmds;
	while (tmp)
	{
		argvt = data->currmds->content;
		if (builtin_exception(data) == 1)
			return (0);
		if (argvt->cmd[0])
			command = (char *)argvt->cmd[0];
		else
			return (-1);
		path = pathfinder(command, data);
		if (!path)
			return (-1);
		free (path);
		tmp = tmp->next;
	}
	return (0);
}

void	all_pipe_close(t_data *data)
{
	int	i;

	i = data->num_pipe; 
	while (i > 0)
	{
		close(data->pipe[i][0]);
		close(data->pipe[i][1]);
		i -- ;
	}
}

char	*new_path_maker(char *input)
{
	char	currentpath[4096];
	char	*newpath;
	int		len;
	int		len_current;

	if (getcwd(currentpath, 4096) == NULL)
	{
		perror("getcwd failed");
		return (NULL);
	}
	len = ft_strlen(currentpath) + ft_strlen(input) + 2;
	newpath = (char *)malloc(sizeof(char) * len);
	if (!newpath)
		return (NULL);
	len_current = ft_strlen(currentpath);
	ft_memset(newpath, 0, len);
	ft_strlcat(newpath, currentpath, len);
	newpath[len_current] = '/';
	newpath[len_current + 1] = '\0';
	ft_strlcat(newpath, input, len);
	return (newpath);
}

void	error_exit(char *msg, int error_number)
{
	perror(msg);
	exit(error_number);
}

void	builtin_situation(t_data *data)
{
	int		code;

	code = 0;
	if (builtin_exception(data) == 1)
	{
		code = builtin(data);
		exit(code);
	}
}
