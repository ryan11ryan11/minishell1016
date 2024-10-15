/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:03:10 by jbober            #+#    #+#             */
/*   Updated: 2024/10/14 15:07:26 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints error message, frees everything and exits with error
 * str = "FILE/LINE ERRORTYPE :(", Errortypes being: failloc, invalid argument:
*/
void	ms_error(t_data *data, char *str, int brexit)
{
	ms_free(data, 1);
	errno = brexit;
	perror(str);
	exit(brexit);
}

/**
 * Frees everything that is bound in shackles, longing for the taste of freedom!
 * modus 1 == clear_history (only at exit)
*/
void	ms_free(t_data *data, int modus)
{
	int	k;

	k = 0;
	if (data->currinput != NULL)
	{
		free(data->currinput);
		data->currinput = NULL;
	}
	ms_freevenmore(data);
	ms_freelst(data->lstart);
	if (modus == 1)
	{
		clear_history();
		if (data->cstrl != NULL)
		{
			while (data->cstrl[k] != NULL)
			{
				free(data->cstrl[k]);
				data->cstrl[k++] = NULL;
			}
			free(data->cstrl);
			data->cstrl = NULL;
		}
	}
}

/**
 * More than 25 lines
*/
void	ms_freevenmore(t_data *data)
{
	int	k;

	k = 0;
	if (data->currstr != NULL)
	{
		while (data->currstr[k] != NULL)
		{
			free(data->currstr[k]);
			data->currstr[k++] = NULL;
		}
		free(data->currstr);
		data->currstr = NULL;
	}
}

/**
 * frees the list \o/
 */
void	ms_freelst(t_list *iamhere)
{
	int	k;
	t_list *tmp;

	k = 0;
	while (iamhere->content->cmd[k])
	{
		free(iamhere->content->cmd[k]);
		iamhere->content->cmd[k++] = NULL;
	}
	free(iamhere->content->cmd);
	iamhere->content->cmd = NULL;
	free(iamhere->content->infd);
	iamhere->content->infd = NULL;
	free(iamhere->content->outfd);
	iamhere->content->outfd = NULL;
	free(iamhere->content);
	iamhere->content = NULL;
	tmp = iamhere;
	if (iamhere->next)
	{
		iamhere = iamhere->next;
		free(tmp);
		tmp = NULL;
		ms_freelst(iamhere);
	}
}
