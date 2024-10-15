/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:38:58 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/14 18:45:16 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdup(const char *src)
{
	char	*tmp;
	int		size;

	if (!src)
		return (NULL);
	size = 0;
	while (src[size] != '\0')
		++size;
	tmp = (char *)malloc((size + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	size = 0;
	while (src[size] != '\0')
	{
		tmp[size] = src[size];
		++size;
	}
	tmp[size] = '\0';
	return (tmp);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	char	**arr_tmp;
	int		i;

	if (!s)
		return (NULL);
	arr = create_matrix(s, c);
	if (!arr)
		return (NULL);
	arr_tmp = arr;
	while (*s != '\0')
	{
		i = 0;
		while (*s != c && *s != '\0')
			(*arr)[i++] = *s++;
		if (i > 0)
		{
			(*arr)[i++] = '\0';
			++arr;
			if (*s == '\0')
				return (arr_tmp);
		}
		++s;
	}
	return (arr_tmp);
}

void	ft_putstr_fd(const char *s, int fd)
{
	while (*s)
		write(fd, s++, sizeof(char));
}

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count] != '\0')
		++count;
	return (count);
}

char	*ft_strchr(const char *s, int ch)
{
	unsigned char	c;

	c = (unsigned char)ch;
	while (*s != c && *s != '\0')
		++s;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}
