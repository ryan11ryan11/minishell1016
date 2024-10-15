/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:38:58 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/15 11:06:04 by junhhong         ###   ########.fr       */
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

static char	**free_matrix(char **end, char **start)
{
	while (end >= start)
		free(*end--);
	free(start);
	return (NULL);
}

static char	**create_str_m(char **arr, char const *s, char c)
{
	size_t	size;
	char	**arr_tmp;

	arr_tmp = arr;
	size = 0;
	while (*s != '\0')
	{
		if (*s != c)
			++size;
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
		{
			*arr_tmp = malloc((size + 1) * sizeof(char));
			if (*arr_tmp == NULL)
				return (free_matrix(arr_tmp, arr));
			++arr_tmp;
			size = 0;
		}
		++s;
	}
	return (arr);
}

static char	**create_matrix(char const *s, char c)
{
	size_t		size;
	char const	*str;
	char		**tmp;

	size = 0;
	str = s;
	while (*str != '\0')
	{
		if (*str != c && (*(str + 1) == c || *(str + 1) == '\0'))
			++size;
		++str;
	}
	tmp = malloc((size + 1) * sizeof(char *));
	if (!tmp)
		return (NULL);
	tmp[size] = NULL;
	return (create_str_m(tmp, s, c));
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
