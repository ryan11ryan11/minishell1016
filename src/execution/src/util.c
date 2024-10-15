/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 19:04:34 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:16:08 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlcmp_limited(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i])
		i ++ ;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char *ft_strcat(char *s1, char *s2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	char	*new;
	i = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new = (char *)malloc(len_s1 + len_s2 + 1);
	if (!new)
		return (NULL);
	while(i < len_s1)
	{
		new[i] = s1[i];
		i++;
	}
	i = 0;
	while(i < len_s2)
	{
		new[len_s1 + i] = s2[i];
		i ++ ;
	}
	new[len_s1 + i] = '\0';
	return (new);
}

