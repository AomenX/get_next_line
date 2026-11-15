/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 22:32:55 by marvin            #+#    #+#             */
/*   Updated: 2026/11/14 22:32:55 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

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

typedef struct s_gnl_node
{
	int					fd;
	t_buffer			buffer;
	struct s_gnl_node	*next;
}	t_gnl_node;

char		*get_next_line(int fd);
void		ft_buffer_compact(t_buffer *buffer);
int			ft_buffer_reserve(t_buffer *buffer, size_t additional);
size_t		ft_next_capacity(size_t capacity, size_t required);
int			ft_buffer_grow(t_buffer *buffer, size_t new_capacity);
int			ft_buffer_find_newline(t_buffer *buffer, size_t from,
				size_t *index);
char		*ft_buffer_extract(t_buffer *buffer, size_t length);
int			ft_buffer_fill(int fd, t_buffer *buffer, size_t *newline);
t_gnl_node	*ft_get_node(t_gnl_node **head, int fd);
void		ft_remove_node(t_gnl_node **head, t_gnl_node *node);

#endif
