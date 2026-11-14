/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 00:22:06 by marvin            #+#    #+#             */
/*   Updated: 2026/11/14 00:22:13 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("tests/single.txt", O_WRONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	if (line == NULL)
		printf("PASS: read error returns NULL\n");
	else
		printf("FAIL: expected NULL\n");
	free(line);
	close(fd);
	return (0);
}
