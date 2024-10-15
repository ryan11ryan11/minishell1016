/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlistclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:12:53 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:14:23 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	envlistclear(t_envlist *envlist)
{
	t_envlist	*tmp;

	while (envlist != NULL)
	{
		tmp = envlist->next;
		free(envlist->value);
		free(envlist);
		envlist = tmp;
	}
}
