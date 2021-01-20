/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:49:03 by hroussea          #+#    #+#             */
/*   Updated: 2021/01/20 15:58:54 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

struct				s_gnl
{
	int				fd;
	int				last_rd;
	char			*buf;
	char			*buf_p_off;
	struct s_gnl	*next;
	int				should_read;
	int				is_valid;
};

struct				s_buf
{
	char			*buf;
	int				len;
	int				last;
};

int					get_next_line(int fd, char **line);
int					gnl_constr(int fd, struct s_gnl *ret);
struct s_gnl		*gnl_get(int fd, struct s_gnl *gnl);
int					read_chunk(struct s_gnl *gnl, struct s_buf *buf);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					buf_add(struct s_buf *buf, char c);
int					gnl_clr_fd(int fd, struct s_gnl *gnl, int ret);
int					check_buffer_size(char **line);

#endif
