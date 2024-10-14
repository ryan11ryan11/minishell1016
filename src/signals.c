/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:17:36 by jbober            #+#    #+#             */
/*   Updated: 2024/08/27 17:31:10 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Manages the handling of SIGINT (ctrl+c) to display a new prompt
 */
void	ms_strc(int sig)
{
	g_lastexit = 130;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (sig == 256)
		return ;
}
// if bla
// damit im childprocess nur dieser gekillt wird
// wenn wir in minishell minishell aufrufen dito
