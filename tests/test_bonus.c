/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/15 00:33:03 by marvin            #+#    #+#             */
/*   Updated: 2026/11/15 00:33:07 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

static int	check(int fd, const char *expected)
{
	char	*line;
	int		ok;

	line = get_next_line(fd);
	ok = (line && strcmp(line, expected) == 0);
	printf("%s: expected [%s]\n", ok ? "PASS" : "FAIL", expected);
	free(line);
	return (!ok);
}

int	main(void)
{
	int	fd1;
	int	fd2;
	int	failed;

	fd1 = open("tests/bonus_a.txt", O_RDONLY);
	fd2 = open("tests/bonus_b.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (1);
	failed = 0;
	failed |= check(fd1, "Apple\n");
	failed |= check(fd2, "Cat\n");
	failed |= check(fd1, "Banana\n");
	failed |= check(fd2, "Dog\n");
	if (get_next_line(fd1) != NULL)
		failed = 1;
	if (get_next_line(fd2) != NULL)
		failed = 1;
	close(fd1);
	close(fd2);
	printf("%s\n", failed ? "BONUS FAILED" : "BONUS PASSED");
	return (failed);
}
