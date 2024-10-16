/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:31 by jbober            #+#    #+#             */
/*   Updated: 2024/10/16 17:00:50 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_parse_ctrl(t_data *data);

/**
 * Control structure
 * Turns the input *str data->currinput into a list (delimiter "|"), containing
 * 		a **str seperating each item (commands, arguments), infd, outfd and
 * 		*path, if applicable
 */
void	ms_parse_ctrl(t_data *data)
{
	if (!(ms_parsefk1_ctrl(data)))
		ms_error(data, "parse/parse/26 failloc :(", ENOMEM);
	if (!(ms_parsefk2_ctrl(data)))
		ms_error(data, "parse/parse/28 failloc :(", ENOMEM);
	// if (!(ms_parsefk3_ctrl(data)))
	// 	ms_error(data, "parse/parse/30 failloc :(", ENOMEM);
	if (!(ms_parsefk4_ctrl(data)))
		ms_error(data, "parse/parse/32 failloc :(", ENOMEM);
	if (!(ms_parsefk5_ctrl(data)))
		ms_error(data, "parse/parse/34 failloc :(", ENOMEM);
}

// echo >