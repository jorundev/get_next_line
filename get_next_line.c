/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:49:06 by hroussea          #+#    #+#             */
/*   Updated: 2021/01/20 16:04:00 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <limits.h>

void			init_buf(char **line, struct s_buf *buf)
{
	buf->buf = *line;
	buf->len = 8;
	buf->last = 0;
	(*line)[buf->len] = 0;
}

int				get_next_line(int fd, char **line)
{
	static struct s_gnl	gnl[OPEN_MAX];
	struct s_gnl		*cur;
	struct s_buf		buf;
	int					tmp;

	if (!check_buffer_size(line) || fd < 0 || read(fd, NULL, 0) == -1 || !line)
		return (-1);
	*line = malloc(9);
	if (!*line)
		return (gnl_clr_fd(fd, &gnl[0], -1));
	init_buf(line, &buf);
	cur = gnl_get(fd, gnl);
	if (!cur)
		return (gnl_clr_fd(fd, &gnl[0], -1));
	tmp = read_chunk(cur, &buf);
	if (!buf_add(&buf, 0))
		return (gnl_clr_fd(fd, &gnl[0], -1));
	*line = buf.buf;
	if (tmp == 0)
		return (gnl_clr_fd(fd, &gnl[0], 0));
	if (tmp != 1)
		return (gnl_clr_fd(fd, &gnl[0], -1));
	return (1);
}

int				gnl_constr(int fd, struct s_gnl *ret)
{
	ret->buf = malloc(BUFFER_SIZE);
	if (!ret->buf)
		return (-1);
	ret->is_valid = 1;
	ret->last_rd = -1;
	ret->next = 0;
	ret->fd = fd;
	ret->should_read = 1;
	return (0);
}

struct s_gnl	*gnl_get(int fd, struct s_gnl *gnl)
{
	if (!gnl[fd].is_valid)
		if (gnl_constr(fd, &gnl[fd]) < 0)
			return (0);
	return (&gnl[fd]);
}

int				read_chunk(struct s_gnl *gnl, struct s_buf *buf)
{
	while (1)
	{
		if (gnl->should_read)
		{
			gnl->buf_p_off = gnl->buf;
			gnl->last_rd = read(gnl->fd, gnl->buf, BUFFER_SIZE);
			gnl->should_read = 0;
			if (gnl->last_rd == 0 || gnl->last_rd == -1)
				return (gnl->last_rd);
		}
		while (gnl->buf_p_off - gnl->buf < gnl->last_rd &&
				*gnl->buf_p_off != '\n')
			buf_add(buf, *gnl->buf_p_off++);
		if (gnl->buf_p_off - gnl->buf >= gnl->last_rd)
		{
			gnl->should_read = 1;
			continue ;
		}
		gnl->buf_p_off++;
		break ;
	}
	return (1);
}
