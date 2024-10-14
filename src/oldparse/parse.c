/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:26:51 by jbober            #+#    #+#             */
/*   Updated: 2024/08/29 13:06:55 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Controls the parsing structure
 */
void	ms_parsecontrol(t_data *data)
{
	ms_sepcmds(data, 0, 0, 0);
	ms_currsplit(data);
	ms_fillst(data);
	m_sexpand(data, data->currmds);
}
