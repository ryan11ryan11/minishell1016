/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ut5ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbober <jbober@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:02:28 by jbober            #+#    #+#             */
/*   Updated: 2024/10/16 13:02:49 by jbober           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_check_qt(char c, int *weakqt, int *strongqt);

/**
 * Checks wether char c is in weak or strong quotes
 * Modifyes qts in case of c being one
 * 0 -> in no quotes
 * 1 -> in weak quotes ""
 * 2 -> in strong quotes ''
 * c = Char to evaluate, weakqt = &weakqt, strongqt = &strongqt
 */
int	ms_check_qt(char c, int *weakqt, int *strongqt)
{
	int i;

	i = 0;
	if (*weakqt % 2)
		i = 1;
	if (*strongqt % 2)
		i = 2;
	if (c == 34 && !(*strongqt % 2))
		(*weakqt)++;
	if (c == 39 && !(*weakqt % 2))
		(*strongqt)++;
	return (i);
}