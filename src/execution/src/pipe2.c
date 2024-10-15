/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:31:08 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/15 12:08:23 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_pipe(t_data *data)
{
	int		num_pipe;
	t_list	*tmp;

	tmp = data->lstart;
	num_pipe = 0;
	while (tmp)
	{
		if (tmp->content->oper == 6)
			num_pipe ++ ;
		tmp = tmp->next;
	}
	return (num_pipe);
}

int	**assign_pipe(int num_pipe)
{
	int	**tmp;
	int	i;

	i = 0;
	tmp = (int **)malloc(num_pipe * sizeof(int *));
	if (!tmp)
		return (NULL);
	while (i < num_pipe)
	{
		tmp[i] = (int *)malloc(2 * sizeof(int));
		if (!tmp[i])
		{
			while (i > 0)
				free(tmp[--i]);
			free (tmp);
			return (NULL);
		}
		i ++ ;
	}
	return (tmp);
}
