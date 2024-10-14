/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakropp <rakropp@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 12:33:36 by rakropp           #+#    #+#             */
/*   Updated: 2024/08/30 12:52:13 by rakropp          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_cmds(t_data *data)
{
	data->currmds = data->lstart;
	while (data->currmds)
	{
		if (ms_strncmp(data->currmds->content->cmd[0], "cd\0", 3) == 0)
			check_cd(data, data->currmds);
		else if ((ms_strncmp(data->currmds->content->cmd[0], "echo\0", 5)) == 0)
			check_echo(data, data->currmds);
		else if ((ms_strncmp(data->currmds->content->cmd[0], "pwd\0", 4)) == 0)
			check_pwd(data, data->currmds);
		else if ((ms_strncmp(data->currmds->content->cmd[0], "export\0", 7)) == 0)
			check_export(data, data->currmds);
		else if ((ms_strncmp(data->currmds->content->cmd[0], "unset\0", 6)) == 0)
			check_unset(data, data->currmds);
		else if ((ms_strncmp(data->currmds->content->cmd[0], "env\0", 4)) == 0)
			check_env(data, data->currmds);
		else if ((ms_strncmp(data->currmds->content->cmd[0], "./", 2)) == 0)
			check_executable(data, data->currmds);
		//else
		//	do_command(data, data->currmds);
	}
}

// check wether there are pipes for non pipable cmds!!!!

void	check_cd(t_data *data, t_node *node)
{
	if (node->cmd[2]) // memorie issues
		ms_error(data, "eidexe/check_cmds.c 44: to many arguments for function call cd", EIO);
	// check if path valid
}

void	check_echo(t_data *data, t_node *node)
{
	// no clue yet
	// check if file??
}

void	check_pwd(t_data *data, t_node *node)
{
	if (node->cmd[1])
		ms_error(data, "eidexe/check_cmds.c 54: to many arguments for function call pwd", EIO);
}

void	check_export(t_data *data, t_node *node)
{
	// check if valid Format
	// check wether there is a file
}

void	check_unset(t_data *data, t_node *node)
{
	// check if file
	// check formate
}

void	check_env(t_data *data, t_node *node)
{
	if (node->cmd[1])
		ms_error(data, "eidexe/check_cmds.c 73: to many arguments for function call env", EIO);
}
