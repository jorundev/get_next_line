/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:49:28 by hroussea          #+#    #+#             */
/*   Updated: 2021/01/20 15:58:45 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int		gnl_clr_fd(int fd, struct s_gnl *gnl, int ret)
{
	gnl[fd].is_valid = 0;
	free(gnl[fd].buf);
	return (ret);
}

int		buf_add(struct s_buf *buf, char c)
{
	char	*tmp;
	int		realloc_size;

	if (buf->last + 1 >= buf->len)
	{
		if (BUFFER_SIZE < 512)
			realloc_size = 512;
		else
			realloc_size = BUFFER_SIZE;
		tmp = malloc(buf->len + realloc_size);
		if (!tmp)
		{
			free(buf->buf);
			return (0);
		}
		ft_memcpy(tmp, buf->buf, buf->len);
		buf->len += realloc_size;
		tmp[buf->len - 1] = 0;
		free(buf->buf);
		buf->buf = tmp;
	}
	buf->buf[buf->last++] = c;
	return (1);
}

int		check_buffer_size(char **line)
{
	if (BUFFER_SIZE < 1)
	{
		*line = 0;
		return (0);
	}
	return (1);
}
