/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:56:01 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:14:45 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	no_argument(t_node *content)
{
	char	*home;

	if (content->cmd[1] == NULL)
	{
		home = getenv("HOME");
		if (chdir(home) == -1)
		{
			perror("Error:");
			return (errno);
		}
		return (0);
	}
	return (-1);
}

int	slash_up(t_node *argvt, char *input)
{	
	if (input[0] == '/' || strcmp(input, "..") == 0)
	{
		if (chdir(argvt->cmd[1]) == -1)
		{
			perror("Error:");
			return (errno);
		}
		else
			return (0);
	}
	return (-1);
}

int	ft_cd(t_data *data)
{
	char	*new_path;
	char	*input;
	int		result;

	input = data->currmds->content->cmd[1];
	result = no_argument(data->currmds->content);
	if (result >= 0)
		return (result);
	result = slash_up(data->currmds->content, input);
	if (result >= 0)
		return (result);
	new_path = new_path_maker(input);
	if (chdir(new_path) == -1)
	{
		perror("Error:");
		free (new_path);
		return (1);
	}
	free (new_path);
	return (0);
}
