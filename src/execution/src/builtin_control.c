/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:57:20 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/16 15:54:20 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	builtin_exception(t_list *node)
{
	if (ft_strlcmp_limited(node->content->cmd[0], "echo") == 0)
		return (1);
	if (ft_strlcmp_limited(node->content->cmd[0], "cd") == 0)
		return (1);
	if (ft_strlcmp_limited(node->content->cmd[0], "pwd") == 0)
		return (1);
	if (ft_strlcmp_limited(node->content->cmd[0], "export") == 0)
		return (1);
	if (ft_strlcmp_limited(node->content->cmd[0], "env") == 0)
		return (1);
	if (ft_strlcmp_limited(node->content->cmd[0], "unset") == 0)
		return (1);
	return (0);
}

int	builtin_exception2(char *arr)
{
	if (ft_strlcmp_limited(arr, "echo") == 0)
		return (1);
	if (ft_strlcmp_limited(arr, "cd") == 0)
		return (1);
	if (ft_strlcmp_limited(arr, "pwd") == 0)
		return (1);
	if (ft_strlcmp_limited(arr, "export") == 0)
		return (1);
	if (ft_strlcmp_limited(arr, "env") == 0)
		return (1);
	if (ft_strlcmp_limited(arr, "unset") == 0)
		return (1);
	return (0);
}

int	ft_strcmp2(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i ++ ;
	}
	return (0);
}

int	builtin(t_data *data, t_list *list)
{
	char	*line;

	line = data->currinput;
	if (ft_strlcmp_limited(list->content->cmd[0], "echo") == 0)
		return (ft_echo(data, list));
	if (ft_strlcmp_limited(list->content->cmd[0], "cd") == 0)
		return (ft_cd(list));
	if (ft_strlcmp_limited(list->content->cmd[0], "pwd") == 0)
		return(ft_pwd());
	if (ft_strlcmp_limited(list->content->cmd[0], "export") == 0)
		return(ft_export(data, line));
	if (ft_strlcmp_limited(list->content->cmd[0], "env") == 0)
		return(ft_env(data));
	if (ft_strlcmp_limited(list->content->cmd[0], "unset") == 0)
		return(ft_unset(data, list));
	return (0);
}

int	count_arg(t_data *data)
{
	int	i;

	i = 0;
	while (data->lstart->content->cmd[i] != NULL)
		i++;
	return (i);
}
