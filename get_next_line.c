/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 23:49:06 by hroussea          #+#    #+#             */
/*   Updated: 2020/11/28 07:51:44 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>

int	read_newline(char *buffer, int *offset, char *line)
{
	size_t	count;

	count = 1;
	while (*offset + count < BUFFER_SIZE)
	{
		if (buffer[*offset + count] == '\n')
		{
			*line = malloc(count);
			ft_strncpy(line, &buffer[*offset], count + 1);
			*offset += count;
			return (1);
		}
		++count;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char		*remainder;
	static size_t	chr;
	static char		**chunks;
	size_t			count;
	size_t			i;

	// on alloue le conteneur de chunks uniquement la première fois
	alloc_if_first(&chunks);
	if (remainder != NULL)
		if (read_newline(remainder, &chr, *line))
		{
			if (chr == BUFFER_SIZE)
			{
				free(remainder);
				remainder = NULL;
			}
			return (1);
		}
	count = 0;
	chunks[0] = malloc(BUFFER_SIZE);
	while (read_next_chunk(fd, chunks[count]) == BUFFER_SIZE) // tant que pas EOF
	{
		i = 0;
		while (i < BUFFER_SIZE)
		{
			if (chunks[count][i] == '\n')
			{
				free(remainder);
				remainder = malloc(BUFFER_SIZE);
				chr = i;
				ft_strncpy(remainder, chunks[count], BUFFER_SIZE + 1);
				*line = malloc(count * BUFFER_SIZE + i);
				ft_strncpy(*line + (count * BUFFER_SIZE + 1), chunks[count], i);
				free(chunks[count]);
				while (count--)
				{
					ft_strncpy(*line + (count * BUFFER_SIZE), chunks[count], BUFFER_SIZE + 1);
					free(chunks[count]);
				}
				return (1);
			}
			++i;
		}
		++count;
		chunks[count] = malloc(BUFFER_SIZE);
	}
	// treat last chunks...
	return (0);
}

int main()
{
	char	*buf;

	while (get_next_line(0, &buf))
	{
		printf("%s\n", buf);	
	}
	return (0);
}
