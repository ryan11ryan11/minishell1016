/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:53:10 by rakropp           #+#    #+#             */
/*   Updated: 2024/10/14 10:41:15 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_arg_u_e(t_data *data, char **arg, int start)
{
	int i;
	int	fd;

	while (arg[start])
	{
		i = 0;
		fd = open(arg[start], O_RDWR);
		if (fd > -1)
		{
			close(fd);
			ms_error(data, "eidexe/unset.c 27: invalid argument(s)", EINVAL);
		}
		while (arg[start][i])
		{
			if (arg[start][i] == '=' && (i == 0 || arg[start][i + 1] == '\0'))
				ms_error(data, "eidexe/unset.c 32: invalid argmunet(s)", EINVAL);
			i++;
		}
		start++;
	}
}

void	fill_arg(t_data *data, char **arg, char **str, int start)
{
	int	c;

	c = 0;
	while (str[start])
		arg[c++] = ms_strdup(str[start++]); // malloc check
	arg[c] = NULL;
	if (data->pid)//silent DataNotUsed-error
		c = 1;
}

int	ms_arglen(char **arg, int start)
{
	int	c;

	c = 0;
	while (arg[start])
	{
		start++;
		c++;
	}
	return (c);
}

void	ms_unset(t_data *data, t_node *node)
{
	char	**unset;
	int		c;

	c = 0;
	if (!(ms_strncmp(node->cmd[c], "unset", 4)))
		c++;
	check_arg_u_e(data, node->cmd, c);
	unset = malloc((ms_arglen(node->cmd, c) + 1) * sizeof (char *));
	if (!unset)
		ms_error(data, "eidexe/unset.c 73:failloc :(", ENOMEM);
	fill_arg(data, unset, node->cmd, c);
	data->env = rm_env(data, unset);
	data->exe->endline = 0;
	g_lastexit = 0;
}

// nimmt ""''
// nimmt $*