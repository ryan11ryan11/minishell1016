/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:47:33 by jbober            #+#    #+#             */
/*   Updated: 2024/10/16 15:24:32 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
volatile sig_atomic_t	g_child;
int	g_lastexit;

void	ms_test(t_data *data, t_list *iamhere)
{
	int	i;
	
	i = 0;
	if (!iamhere)
		return ;
	printf("\n...\t Start List\t...\n");
	while (iamhere->content && iamhere->content->cmd[i])
	{
		printf("cmd[%i] == %s\n", i, iamhere->content->cmd[i]);
		i++;
	}
	printf("infd == %s\noutfd == %s\nstatus == %i\noper == %i\n", iamhere->content->infd, iamhere->content->outfd, iamhere->content->status, iamhere->content->oper);
	ms_test(data, iamhere->next);
}

//-----------------------------------------------------

/**
 * Initializes values to zero
*/
void	ms_initialize(t_data *data, char **envp)
{
	(void) envp;
	data->exe = (t_exe *)malloc(sizeof(t_exe));
	data->currinput = NULL;
	data->currstr = NULL;
	ms_ctrlitialize(data);
	g_lastexit = 0;
	//data->exe->std_fd[0] = dup(0);
	//data->exe->std_fd[1] = dup(1);
	data->env = NULL;
	ms_envp(data, envp);
	data->exe->endline = 0;
	data->env_set = 0;
	data->new_envp = NULL;
}

/**
 * Displays a prompt as: ~/../LOCATION as in pwd
*/
void	ms_prompt(t_data *data)
{
	char	*thisdir;

	thisdir = getcwd(NULL, 0);
	thisdir = ms_speciasplit(data, thisdir);
	if (data->exe->endline == 0)
	{
		printf("~/..%s", thisdir);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else
		printf("~/..%s", thisdir);
	free(thisdir);
}

int	case_exit(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i ++ ;
	if (line[i] == 'e' && line[i + 1] == 'x' && line[i + 2] == 'i' \
	&& line[i + 3] == 't')
		return (1);
	return (0);
}

int	terminatation(char *line)
{
	if (case_exit(line) == 1)
		return (1);
	return (0);
}


/**
 * Extends the prompt with:_:)__
 * Saves the input to data->currinput as well as history
*/
int	ms_read_input(t_data *data)
{
	char	*cwd;
	char	*new_cwd;

	cwd = getcwd(NULL,0);
	new_cwd = ft_strcat(cwd,"$ ");
	data->currinput = readline(new_cwd);
	free(new_cwd);
	free(cwd);
	if (!data->currinput || terminatation(data->currinput) == 1) //EOF
		ms_error(data, "minishell.c 73: failloc :(", ENOMEM);
	if (ms_strlen(data->currinput) != 0)
	{
		add_history(data->currinput);
		return (0);
	}
	return (1);
}

void	print_all_cmd(char **cmd)
{
	int	i;

	i = 0;
	while(cmd[i])
	{
		printf("cmd[%d]:%s\n",i,cmd[i]);
		i ++ ;
	}
}

void	test_print(t_data *data)
{
	t_list *tmp;

	tmp = data->lstart;
	while(tmp)
	{
		printf("******************************************************\n");
		printf("oper:	%d		status:		%d\n",tmp->content->oper,tmp->content->status);
		print_all_cmd(tmp->content->cmd);
		printf("infd:	%s\n",tmp->content->infd);
		printf("outfd:	%s\n",tmp->content->outfd);
		tmp = tmp->next;
	}
	printf("******************************************************\n");
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data = {0};

	
	ms_initialize(&data, envp);
	(void)argc;
	(void)argv;
	//signal(SIGINT, ms_strc);
	//signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ft_signal();
		//ms_prompt(&data);
		if (ms_read_input(&data) == 1)
			continue ;
		if (data.env_set == 0)
			envlistmaker(&data, envp);
		envp_maker(&data);
		ms_parse_ctrl(&data); // here print
		data_setting(&data); // problem
		exec_command(&data);
		test_print(&data);
		printf("%d\n",data.errcode);
		//exe_control(&data);
		//ms_free(&data, 0);
	}
	ms_free(&data, 1);
	g_lastexit = 0;
	exit(g_lastexit);
}
