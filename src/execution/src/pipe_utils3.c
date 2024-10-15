/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:41:00 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/15 12:22:19 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern volatile sig_atomic_t	g_child;

void	case_outfile(t_node *argvt)
{
	int	fd;

	if (argvt->appnd == 0)
		fd = open(argvt->outfd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (argvt->appnd == 1)
		fd = open(argvt->outfd, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror("Error:");
		exit (1);
	}
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

char	*get_last_word(char *buffer, int index)
{
	char	**split;
	char	*last;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(buffer);
	tmp[index] ='\0';
	split = ft_split(tmp, '\n');
	if (!split)
		return (NULL);
	while(split[i + 1] != NULL)
		i ++;
	last = ft_strdup(split[i]);
	doublearr_free(&split);
	free(tmp);
	return (last);
}

void	case_heredoc(t_data *data)
{
	char	buffer[2048];
	int		total_byte;
	int		byte_read;
	char	*delimiter;
	char	*last_word;
	int		fd[2];
	pid_t	pid;

	if (!data->lstart->next)
	{
		ft_putstr_fd("syntax error\n", 2);
		exit (2);
	}
	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		delimiter = (char *)(data->lstart->next->content->cmd[0]);
		total_byte = 0;
		while(1)
		{	
			write(1, "> ", 2);
			byte_read = read(STDIN_FILENO, buffer + total_byte, sizeof(buffer) - total_byte - 1);
			total_byte = total_byte + byte_read;
			last_word = get_last_word(buffer, total_byte - 1);
			if (ft_strlcmp_limited(last_word, delimiter) == 0)
				break;
		}
		buffer[total_byte - 1 - ft_strlen(last_word)] = '\0';
		close(fd[0]);
		write(fd[1], buffer, ft_strlen(buffer));
		close(fd[1]);
		exit (0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		waitpid(pid, NULL, 0);
	}
}


int	case_infile(t_data *data)
{
	int		fd;
	t_node	*argvt;

	argvt = data->lstart->content;
	if (argvt->appnd == 0)
	{
		fd = open(argvt->infd, O_RDONLY);
		if (fd == -1)
		{
			perror("Error:");
			exit (1);
		}
		dup2(fd, STDIN_FILENO);
		close (fd);
	}
	return (0);
}

t_list	*prv_list_finder(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp == list)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	child_process(t_data *data, int i)
{
	char	*command;
	char	*path;
	t_list	*prv_list;
	//t_node	*argvt;
	t_list	*list;

	list = data->lstart;
	command = NULL;
	prv_list = NULL;
	//argvt = data->lstart->content;
	if (prv_list_finder(list))
		prv_list = prv_list_finder(list);
	if (prv_list->content->oper == 1)
		exit (0);
	if ((list->content->oper == 6) || (prv_list && prv_list->content->oper == 6))
		exec_pipe(data, i);
	if (list->content->outfd != NULL)
		case_outfile(list->content);
	if (list->content->infd != NULL)
		case_infile(data);
	if (list->content->oper == 1)
		case_heredoc(data); // argv[0]이상 있을 경우?
	// if ((argvt->oper == 6) || (prv_argvt && prv_argvt->oper == 6))
	// 	exec_pipe(info, i);
	if (list->content->cmd[0])
		command = list->content->cmd[0];
	else
		perror("error");
	builtin_situation(data);
	path = pathfinder(command, data);
	if (!path)
		error_exit(command, 1);
	if (path && (char *const *)list->content->cmd && data->new_envp)
	{
		envp_maker(data);
		execve(path, (char *const *)list->content->cmd, data->new_envp);
		error_exit("execve error", 1);
	}
}

void	parent_process(t_data *data)
{
	int	j;
	int	status;
	int	exit_code;

	j = 0;
	while(j < data->num_pipe)
	{
		close(data->pipe[j][0]);
		close(data->pipe[j][1]);
		j ++;
	}
	j = 0;
	while(j < data->num_ndata)
	{
		waitpid(data->pid[j], &status, 0);
		j ++;
	}
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		data->errcode = exit_code;
	}
}

int	exec_command_errcheck(t_data *data)
{
	t_node	*argvt;

	argvt = data->lstart->content;
	if (ft_get_env(data) == NULL &&
	ft_strlcmp_limited(argvt->cmd[0], "export") != 0)
	{
		data->errcode = 127;
		ft_putstr_fd("command not found\n", 1);
		return (-1);
	}
	if (all_component_check(data) == -1)
	{
		perror("ERROR");
		return (-1);
	}
	else
		return (1);
}

int	parent_process_exec(t_data *data)
{
	char **argv;

	argv = data->lstart->content->cmd;
	if (ft_strlcmp_limited(argv[0], "export") == 0)
		return(ft_export(data, data->currinput));
	if (ft_strlcmp_limited(argv[0], "unset") == 0)
		return(ft_unset(data));
	if (ft_strlcmp_limited(argv[0], "cd") == 0)
		return (ft_cd(data));
	if (ft_strlcmp_limited(argv[0], "env") == 0)
		return(ft_env(data));
	if (ft_strlcmp_limited(argv[0], "pwd") == 0)
		return(ft_pwd());
	if (ft_strlcmp_limited(argv[0], "echo") == 0)
		return(ft_echo(data));
	return (1);
}

int		is_pipe(t_list *lstart, t_data *data)
{
	t_node *argvt;

	while(lstart)
	{
		argvt = data->lstart->content;
		if (argvt->oper == 6)
			return (1);
		if (argvt->infd != NULL)
			return (1);
		if (argvt->outfd != NULL)
			return (1);
		lstart = lstart->next;
	}
	return (-1);
}

void	exec_command(t_data *data)
{
	int		i;
	t_node	*argvt;

	argvt = data->lstart->content;

	if (exec_command_errcheck(data) == -1)
		return ;
	if (is_pipe(data->lstart, data) == -1 && builtin_exception(data) == 1)
	{
		data->errcode = parent_process_exec(data);
		return ;
	}
	i = -1;
	while (data->lstart)
	{
		i ++;
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			child_process(data, i);
		data->lstart = data->lstart->next;
	}
	parent_process(data);
}
