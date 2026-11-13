/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:56:45 by marvin            #+#    #+#             */
/*   Updated: 2026/11/12 18:55:37 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_buffer_compact(t_buffer *buffer)
{
	size_t	remaining;
	size_t	i;

	if (buffer->start == 0)
		return ;
	i = 0;
	remaining = buffer->end - buffer->start;
	while (i < remaining)
	{
		buffer->data[i] = buffer->data[buffer->start + i];
		i++;
	}
	buffer->start = 0;
	buffer->end = remaining;
}

int	ft_buffer_reserve(t_buffer *buffer, size_t additional)
{
	size_t	remaining;
	size_t	required;
	size_t	new_capacity;

	remaining = buffer->end - buffer->start;
	if (buffer->capacity - buffer->end >= additional)
		return (1);
	if (additional > SIZE_MAX - remaining)
		return (0);
	required = remaining + additional;
	if (buffer->capacity >= required)
	{
		ft_buffer_compact(buffer);
		return (1);
	}
	new_capacity = ft_next_capacity(buffer->capacity, required);
	return (ft_buffer_grow(buffer, new_capacity));
}

size_t	ft_next_capacity(size_t capacity, size_t required)
{
	size_t	new_capacity;

	new_capacity = capacity;
	if (new_capacity == 0)
		new_capacity = 1;
	while (new_capacity < required)
	{
		if (new_capacity > SIZE_MAX / 2)
		{
			new_capacity = required;
			break ;
		}
		new_capacity *= 2;
	}
	return (new_capacity);
}

int	ft_buffer_grow(t_buffer *buffer, size_t new_capacity)
{
	size_t	i;
	char	*new_data;
	size_t	remaining;

	remaining = buffer->end - buffer->start;
	new_data = malloc(new_capacity);
	if (!new_data)
		return (0);
	i = 0;
	while (i < remaining)
	{
		new_data[i] = buffer->data[buffer->start + i];
		i++;
	}
	free(buffer->data);
	buffer->data = new_data;
	buffer->capacity = new_capacity;
	buffer->start = 0;
	buffer->end = remaining;
	return (1);
}

int	ft_buffer_find_newline(t_buffer *buffer, size_t from, size_t *index)
{
	size_t	i;

	i = from;
	while (i < buffer->end)
	{
		if (buffer->data[i] == '\n')
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}
