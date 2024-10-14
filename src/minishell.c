/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:47:33 by jbober            #+#    #+#             */
/*   Updated: 2024/08/29 14:30:11 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Initializes values to zero
*/
void	ms_initialize(t_data *data, char **envp)
{
	data->currinput = NULL;
	data->currstr = NULL;
	ms_ctrlitialize(data);
	g_lastexit = 0;
	data->exe->std_fd[0] = dup(0);
	data->exe->std_fd[1] = dup(1);
	ms_envp(data, envp);
	data->exe->endline = 0;
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
		printf("\n~/..%s", thisdir);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else
		printf("~/..%s", thisdir);
	free(thisdir);
}

/**
 * Extends the prompt with:_:)__
 * Saves the input to data->currinput as well as history
*/
int	ms_read_input(t_data *data)
{
	data->currinput = readline(" :)  ");
	if (!data->currinput)//EOF
		ms_error(data, "minishell.c 73: failloc :(", ENOMEM);
	if (ms_strlen(data->currinput) != 0)
	{
		add_history(data->currinput);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	ms_initialize(&data, envp);
	(void)argc;
	(void)argv;
	//signal(SIGINT, ms_strc);
	//signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		ms_prompt(&data);
		if (ms_read_input(&data) == 1)
			continue ;
		data.exe->endline = 0;
		ms_parse_ctrl(&data);
		exe_control(&data);
		ms_free(&data, 0);
	}
	ms_free(&data, 1);
	g_lastexit = 0;
	exit(g_lastexit);
}
