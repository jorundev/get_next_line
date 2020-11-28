/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:49:28 by hroussea          #+#    #+#             */
/*   Updated: 2020/11/28 07:48:51 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_next_chunk(int fd, char *buf)
{
	return (read(fd, buf, BUFFER_SIZE));
}

void	alloc_if_first(char	***chunks)
{
	static int	not_first;

	if (!not_first)
	{
		not_first = 1;
		*chunks = malloc(sizeof(char *) * 1024);
	}
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstc;
	unsigned char	*srcc;

	if (dst == src)
		return (dst);
	dstc = (unsigned char*)dst;
	srcc = (unsigned char*)src;
	while (n)
	{
		*dstc++ = *srcc++;
		--n;
	}
	return (dst);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = 0;
		++i;
	}
	return (dest);
}
