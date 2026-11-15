/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 16:41:59 by marvin            #+#    #+#             */
/*   Updated: 2026/11/14 16:39:41 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_buffer_extract(t_buffer *buffer, size_t length)
{
	char	*line;
	size_t	remaining;
	size_t	i;

	remaining = buffer->end - buffer->start;
	if (length == 0 || length > remaining || length == SIZE_MAX)
		return (NULL);
	line = malloc(length + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < length)
	{
		line[i] = buffer->data[buffer->start + i];
		i++;
	}
	line[i] = '\0';
	buffer->start += length;
	return (line);
}

int	ft_buffer_fill(int fd, t_buffer *buffer, size_t *newline)
{
	ssize_t	bytes_read;
	size_t	scan_start;

	if (ft_buffer_newline(buffer, buffer->start, newline))
		return (1);
	while (1)
	{
		if (!(ft_buffer_reserve(buffer, BUFFER_SIZE)))
			return (-1);
		scan_start = buffer->end;
		bytes_read = read(fd, buffer->data + buffer->end, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			return (0);
		buffer->end += bytes_read;
		if (ft_buffer_newline(buffer, scan_start, newline))
			return (1);
	}
}

void	ft_buffer_clear(t_buffer *buffer)
{
	free(buffer->data);
	buffer->data = NULL;
	buffer->capacity = 0;
	buffer->start = 0;
	buffer->end = 0;
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	size_t			newline;
	size_t			length;
	int				status;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = ft_buffer_fill(fd, &buffer, &newline);
	if (status == -1 || (status == 0 && buffer.start == buffer.end))
	{
		ft_buffer_clear(&buffer);
		return (NULL);
	}
	if (status == 1)
		length = newline - buffer.start + 1;
	else
		length = buffer.end - buffer.start;
	line = ft_buffer_extract(&buffer, length);
	if (!line || buffer.start == buffer.end)
		ft_buffer_clear(&buffer);
	return (line);
}
