/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:40:45 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:15:32 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_ctrl_c(int signum)
{
	(void) signum;
	printf("heredoc ctrl_c signal catched\n");
	exit(1);
}

void	heredoc_signal(void)
{
	signal(SIGINT, heredoc_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
