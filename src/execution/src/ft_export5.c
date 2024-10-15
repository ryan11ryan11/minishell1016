/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 17:06:36 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:15:19 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_alphabet(char *name, t_data *data)
{
	if ('0' <= name[0] && name[0] <= '9')
	{
		ft_putstr_fd ("export: not a valid identifier\n", 2);
		data->errcode = 1;
		return (1);
	}
	return (-1);
}

int	add_arr(char **arr, char *new)
{
	int	i;

	i = 0;
	if (!arr || !new)
		return (-1);
	while (arr[i] != NULL)
		i ++ ;
	arr[i] = ft_strdup(new);
	return (1);
}
