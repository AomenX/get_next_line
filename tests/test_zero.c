/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 00:22:46 by marvin            #+#    #+#             */
/*   Updated: 2026/11/14 00:22:50 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../get_next_line.h"
#include <stdio.h>

int	main(void)
{
	if (get_next_line(0) == NULL)
	{
		printf("PASS: invalid BUFFER_SIZE\n");
		return (0);
	}
	return (1);
}
