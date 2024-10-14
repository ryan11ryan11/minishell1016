/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:50:46 by rakropp           #+#    #+#             */
/*   Updated: 2024/08/23 15:52:44 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Checks wether the argument node->cmd[i] is a viable -n flag ('-' + any number of small 'n's only)
 * Returns 1 if yes, 0 if no
 */
static int	ms_echo_n(t_node *node, int i)
{
	int	j;

	j = 1;
	if (node->cmd[i][0] == 45)
	{
		while (node->cmd[i][j])
		{
			if (node->cmd[i][j] != 110)
				return (0);
			j++;
		}
		return (1);
	}
	return (0);
}

void	ms_echo(t_data *data, t_node *node)
{
	int	i;
	int	j;

	i = 0;
	if (!(ms_strncmp(node->cmd[i], "echo", 4)))
		i++;
	j = ms_echo_n(node, i);
	if (j == 1)
		i++;
	if (ms_arglen(node->cmd, i) > 0)
	{
		while (node->cmd[i])
		{
			printf("%s", node->cmd[i++]);
			if (node->cmd[i])
				printf(" ");
		}
	}
	if (j == 0)
	{
		printf("\n");
		data->exe->endline = 1;
	}
	g_lastexit = 0;
}
