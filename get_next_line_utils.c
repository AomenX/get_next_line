/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:56:45 by marvin            #+#    #+#             */
/*   Updated: 2026/11/11 11:15:28 by ammomen          ###   ########.fr       */
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
