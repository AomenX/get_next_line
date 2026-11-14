/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ammomen <ammomen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/14 13:34:50 by marvin            #+#    #+#             */
/*   Updated: 2026/11/14 13:34:51 by ammomen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

static int	test_file(const char *path, const char **expected,
		size_t count)
{
	int		fd;
	size_t	i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("FAIL: cannot open %s\n", path), 1);
	i = 0;
	while (i < count)
	{
		line = get_next_line(fd);
		if (!line || strcmp(line, expected[i]) != 0)
		{
			printf("FAIL: %s, line %zu\n", path, i + 1);
			free(line);
			close(fd);
			return (1);
		}
		free(line);
		i++;
	}
	line = get_next_line(fd);
	if (line)
	{
		printf("FAIL: %s, expected NULL at EOF\n", path);
		free(line);
		close(fd);
		return (1);
	}
	close(fd);
	printf("PASS: %s\n", path);
	return (0);
}

int	main(void)
{
	const char	*single[] = {"ABC\n"};
	const char	*no_newline[] = {"ABC"};
	const char	*multiple[] = {"ABC\n", "DEF\n", "GHI"};
	const char	*blank[] = {"\n", "\n"};
	const char	*long_expected[2];
	char		big[1002];
	int			failed;

	memset(big, 'A', 1000);
	big[1000] = '\n';
	big[1001] = '\0';
	long_expected[0] = big;
	long_expected[1] = "Z";
	failed = 0;
	failed |= test_file("tests/empty.txt", NULL, 0);
	failed |= test_file("tests/single.txt", single, 1);
	failed |= test_file("tests/no_newline.txt", no_newline, 1);
	failed |= test_file("tests/multiple.txt", multiple, 3);
	failed |= test_file("tests/blank.txt", blank, 2);
	failed |= test_file("tests/long.txt", long_expected, 2);
	if (get_next_line(-1) != NULL)
	{
		printf("FAIL: invalid fd\n");
		failed = 1;
	}
	if (!failed)
		printf("\nALL TESTS PASSED!\n");
	return (failed);
}
