/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:04:31 by jbober            #+#    #+#             */
/*   Updated: 2024/10/16 13:25:58 by jbober           ###   ########.fr       */
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
	if (!(ms_parsefk2_ctrl(data)))//set expanded value in "", so they get removed later
		ms_error(data, "parse/parse/28 failloc :(", ENOMEM);
	if (!(ms_parsefk3_ctrl(data)))
		ms_error(data, "parse/parse/30 failloc :(", ENOMEM);
	if (!(ms_parsefk4_ctrl(data)))
		ms_error(data, "parse/parse/32 failloc :(", ENOMEM);
	if (!(ms_parsefk5_ctrl(data)))
		ms_error(data, "parse/parse/34 failloc :(", ENOMEM);
}

// Potential Problems:
// export test="    la" -> jedes space wird ein cmd[k]
//		- put output in "", trim later (?? aaa)
// export test=""		-> ein cmd[k] ist "", siehe echo "test"


// Problems:
// echo "test" should be test, is "test", same with 'test'
//		"'test'" is 'test, but "'"test"'" is 'test', "'"'"'test'"'"'" is '"test"
// echo "test is waiting for input -> ignores missing "

// -->maybe those are solved by the exepart?