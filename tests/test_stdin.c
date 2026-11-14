/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 00:20:57 by marvin            #+#    #+#             */
/*   Updated: 2026/11/14 00:21:07 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../get_next_line.h"
#include <stdio.h>

int	main(void)
{
	char	*line;

	while ((line = get_next_line(0)) != NULL)
	{
		printf("LINE: [%s]\n", line);
		free(line);
	}
	return (0);
}
