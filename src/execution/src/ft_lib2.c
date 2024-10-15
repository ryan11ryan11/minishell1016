/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lib2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junhhong <junhhong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:47:52 by junhhong          #+#    #+#             */
/*   Updated: 2024/10/15 10:51:53 by junhhong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t	i;

	if (!dest)
		return (NULL);
	if (len <= 0 || !src)
		return (dest);
	dest[len] = '\0';
	i = -1;
	while (++i < len)
		dest[i] = src[i];
	return (dest + len);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		++src_len;
	if (size <= 0)
		return (src_len);
	if (size > src_len)
		size = src_len + 1;
	dest[--size] = '\0';
	while (size)
	{
		--size;
		dest[size] = src[size];
	}
	return (src_len);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	byte;

	str = (unsigned char *)s;
	byte = (unsigned char)c;
	while ((n--) > 0)
		str[n] = byte;
	return (s);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t			dest_size;
	size_t			src_size;
	size_t			left_size;
	unsigned int	i;

	dest_size = 0;
	src_size = 0;
	while (dest[dest_size] != '\0' && dest_size < size)
		dest_size++;
	while (src[src_size] != '\0')
		src_size++;
	if (dest_size >= size)
		return (size + src_size);
	left_size = size - dest_size - 1;
	i = 0;
	while (src[i] != '\0' && i < left_size)
	{
		dest[dest_size + i] = src[i];
		i++;
	}
	dest[dest_size + i] = '\0';
	return (dest_size + src_size);
}

