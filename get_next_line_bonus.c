/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 22:33:06 by marvin            #+#    #+#             */
/*   Updated: 2026/11/15 00:23:42 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_gnl_node	*ft_get_node(t_gnl_node **head, int fd)
{
	t_gnl_node	*node;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = malloc(sizeof(t_gnl_node));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->buffer.data = NULL;
	node->buffer.capacity = 0;
	node->buffer.start = 0;
	node->buffer.end = 0;
	node->next = *head;
	*head = node;
	return (node);
}

void	ft_remove_node(t_gnl_node **head, t_gnl_node *node)
{
	t_gnl_node	**link;

	link = head;
	while (*link && *link != node)
		link = &(*link)->next;
	if (!*link)
		return ;
	*link = node->next;
	free(node->buffer.data);
	free(node);
}

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

	if (ft_buffer_find_newline(buffer, buffer->start, newline))
		return (1);
	while (1)
	{
		if (!ft_buffer_reserve(buffer, BUFFER_SIZE))
			return (-1);
		scan_start = buffer->end;
		bytes_read = read(fd, buffer->data + buffer->end, BUFFER_SIZE);
		if (bytes_read < 0)
			return (-1);
		if (bytes_read == 0)
			return (0);
		buffer->end += bytes_read;
		if (ft_buffer_find_newline(buffer, scan_start, newline))
			return (1);
	}
}

char	*get_next_line(int fd)
{
	static t_gnl_node	*head;
	t_gnl_node			*node;
	size_t				newline;
	int					status;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	node = ft_get_node(&head, fd);
	if (!node)
		return (NULL);
	status = ft_buffer_fill(fd, &node->buffer, &newline);
	if (status == -1 || (status == 0
			&& node->buffer.start == node->buffer.end))
		return (ft_remove_node(&head, node), NULL);
	if (status == 1)
		line = ft_buffer_extract(&node->buffer,
				newline - node->buffer.start + 1);
	else
		line = ft_buffer_extract(&node->buffer,
				node->buffer.end - node->buffer.start);
	if (!line || node->buffer.start == node->buffer.end)
		ft_remove_node(&head, node);
	return (line);
}
