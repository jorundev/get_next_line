/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:49:03 by hroussea          #+#    #+#             */
/*   Updated: 2020/11/28 07:57:16 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE	10000

int		get_next_line(int fd, char **line);
int		read_next_chunk(int fd, char *buf);
void	alloc_if_first(char	***chunks);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

#endif