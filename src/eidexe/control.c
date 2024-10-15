/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:31:45 by rakropp           #+#    #+#             */
/*   Updated: 2024/10/14 11:09:48 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_wo_quots(t_node *node, int c, int g)
{
	char	*ret;
	int		i;
	int		t;

	i = 0;
	t = 0;
	ret = malloc((ms_strlen(node->cmd[c]) - g + 1));
	if (!ret)
		return (NULL);
	while (node->cmd[c][i])
	{
		if (node->cmd[c][i] == 34 || node->cmd[c][i] == 39)
			i++;
		ret[t++] = node->cmd[c][i++];
	}
	ret[t] = '\0';
	return (ret);
}

void	ms_rm_quots(t_node *node)
{
	int	c;
	int	i;
	int	g;

	c = 0;
	g = 0;
	while (node->cmd[c])
	{
		i = 0;
		g = 0;
		while (node->cmd[c][i])
		{
			if (node->cmd[c][i] == 34 || node->cmd[c][i] == 39)
				g++;
			i++;
		}
		node->cmd[c] = copy_wo_quots(node, c, g); // needs to be freed
		c++;
	}
}

void	find_cmd(t_data *data, t_node *node)
{
	if ((ms_strncmp(node->cmd[0], "cd\0", 3)) == 0)
		ms_cd(data, node);
	else if ((ms_strncmp(node->cmd[0], "echo", 4)) == 0)
		ms_echo(data, node);
	else if ((ms_strncmp(node->cmd[0], "pwd", 3)) == 0)
		ms_pwd(data, node);
	else if ((ms_strncmp(node->cmd[0], "export\0", 7)) == 0)
		ms_export(data, node);
	else if ((ms_strncmp(node->cmd[0], "unset\0", 6)) == 0)
		ms_unset(data, node);
	else if ((ms_strncmp(node->cmd[0], "env\0", 4)) == 0)
		ms_env(data, node);
	else if ((ms_strncmp(node->cmd[0], "./", 2)) == 0)
		ms_executable(data, node);
	// else
	// 	do_command(data, node);
	dup2(data->exe->std_fd[0], 0);
	dup2(data->exe->std_fd[1], 1);
}

void	sort_in_out(t_data *data, t_node *node)
{
	int i;

	i = 0;
	while (node->cmd[i] && node->cmd[i][0] == '<')
		i++;
	if (node->infd != 0)
		dup2(node->infd, 0);
	else if (data->currmds == data->lstart || node->cmd[i][0] == '<')
		dup2(data->exe->std_fd[0], 0);
	else
		dup2(data->exe->tube[0], 0);
	if (data->exe->tube[0])
		close(data->exe->tube[0]);
	if (node->outfd != 1)
		dup2(node->outfd, 1);
	else if (data->exe->pipehowmuch > 1)
		dup2(data->exe->tube[1], 1);
	else
		dup2(data->exe->std_fd[1], 1);
	if (data->exe->tube[1] != 1)
		close(data->exe->tube[1]);
}

// void	find_path(t_data *data, t_node *node)
// {
// 	int		c;
// 	char	*tmp;
// 	char	*cmdpath;
// 	char	*exe;

// 	c = 0;
// 	if (node->path)
// 		return ;
// 	if ((ms_strncmp(node->cmd[0], "./", 2)) == 0)
// 		exe = ms_substr(data, node->cmd[0], 2, ms_strlen(node->cmd[0]));
// 	else
// 		exe = ms_strdup(node->cmd[0]);
// 	if (!exe)
// 		ms_error(data, "FILE/LINE failloc", 8);
// 	while (data->exe->paths[c])
// 	{
// 		tmp = ms_strjoin(data->exe->paths[c], "/");
// 		if (!tmp)
// 		{
// 			free(exe);
// 			ms_error(data, "eidexe/control.c 82: failloc :(", ENOMEM);
// 		}
// 		cmdpath = ms_strjoin(tmp, exe);
// 		if (!cmdpath)
// 		{
// 			free(exe);
// 			free(tmp);
// 			ms_error(data, "eidexe/control.c 89: failloc :(", ENOMEM);
// 		}
// 		free(tmp);
// 		if (access(cmdpath, 0) == 0)
// 		{
// 			node->path = ms_strdup(cmdpath);
// 			if (!node->path)
// 				ms_error(data, "FILE/LINE failloc", 8);
// 			free(cmdpath);
// 			free(exe);
// 			return ;
// 		}
// 		free(cmdpath);
// 		c++;
// 	}
// 	free(exe);
// 	ms_error(data, "eidexe/control.c 92: invalid PATH", EIO);
// }

void	sort_node(t_data *data, t_node *node)
{
	ms_rm_quots(node);
	data->pid = fork();
	if (data->pid == 0)
	{
		sort_in_out(data, node);
		find_cmd(data, node);
	}
	waitpid(data->pid, NULL, 0);
	data->pid = -2;
}

void	get_pipes(t_data *data)
{
	data->exe->pipehowmuch = 1;
	data->currmds = data->lstart;
	while (data->currmds->next)
	{
		data->currmds = data->currmds->next;
		data->exe->pipehowmuch++;
	}
}

void	exe_control(t_data *data)
{
	if (!data->lstart)
		return ;
	get_pipes(data);
	//check_cmds(data);
	data->currmds = data->lstart;
	if (pipe(data->exe->tube))
		ms_error(data, "eidexe/control.c 126", EPIPE);
	//data->exe->path = getenv("PATH");
	//data->exe->paths = ms_split(data, data->exe->path, ':');
	sort_node(data, data->currmds->content);
	data->exe->pipehowmuch--;
	while (data->exe->pipehowmuch >= 0 && data->currmds->next)
	{
		sort_node(data, data->currmds->next->content);
		data->exe->pipehowmuch--;
		data->currmds = data->currmds->next;
	}
}

// todo $* 
// todo $?
// todo '' "" done
// what happens when single quote?

// data->endline einfügen done

// Fehlermeldung falscher Command

// exit cmd weird error massage
