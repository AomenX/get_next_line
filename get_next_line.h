/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 10:50:49 by marvin            #+#    #+#             */
/*   Updated: 2026/11/11 21:09:15 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	char	*data;
	size_t	capacity;
	size_t	start;
	size_t	end;
}	t_buffer;

char	*get_next_line(int fd);
void	ft_buffer_compact(t_buffer *buffer);
int		ft_buffer_reserve(t_buffer *buffer, size_t additional);
size_t	ft_next_capacity(size_t capacity, size_t required);
int		ft_buffer_grow(t_buffer *buffer, size_t new_capacity);
int		ft_buffer_find_newline(t_buffer *buffer, size_t *index);
char	*ft_buffer_extract(t_buffer *buffer, size_t newline_index);

#endif
