/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:44:56 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/15 17:49:08 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*without_data(char *str)
{
	char	*newstr;
	int		i;
	int		j;

	i = ms_strlen(str) - 1;
	j = 0;
	while (str[i] && str[i] != 47)
		i--;
	newstr = malloc((ms_strlen(str) - i + 1) * sizeof(char));
	while (str[i])
		newstr[j++] = str[i++];
	newstr[j] = '\0';
	free (str);
	return (newstr);
}

void	print_current_path()
{
	char	*thisdir;

	thisdir = getcwd(NULL, 0);
	thisdir = without_data(thisdir);
	printf("~/..%s", thisdir);
}
