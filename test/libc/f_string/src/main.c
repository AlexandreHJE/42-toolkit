/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qperez <qperez42@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/09/27 15:48:40 by qperez            #+#    #+#             */
/*   Updated: 2013/11/05 14:38:03 by qperez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>
#include <f_string/f_char.h>
#include <f_string/f_print_fd.h>
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

static void
is_upper(void **state) {
	for (unsigned char c = 0; c < CHAR_MAX; c++) {
		assert_true(!!isupper(c) == uf_is_upper(c));
	}
	(void)state;
}

static void
is_lower(void **state) {
	for (unsigned char c = 0; c < CHAR_MAX; c++) {
		assert_true(!!islower(c) == uf_is_lower(c));
	}
	(void)state;
}

static void
is_alpha(void **state) {
	for (unsigned char c = 0; c < CHAR_MAX; c++) {
		assert_true(!!isalpha(c) == uf_is_alpha(c));
	}
	(void)state;
}

static void
is_digit(void **state) {
	for (unsigned char c = 0; c < CHAR_MAX; c++) {
		assert_true(!!isdigit(c) == uf_is_digit(c));
	}
	(void)state;
}

static void
is_print(void **state) {
	for (unsigned char c = 0; c < CHAR_MAX; c++) {
		assert_true(!!isprint(c) == uf_is_printable(c));
	}
	(void)state;
}

static void
to_upper(void **state) {
	for (unsigned char c = 0; c < CHAR_MAX; c++) {
		assert_true(toupper(c) == uf_to_upper(c));
	}
	(void)state;
}

static void
to_lower(void **state) {
	for (unsigned char c = 0; c < CHAR_MAX; c++) {
		assert_true(tolower(c) == uf_to_lower(c));
	}
	(void)state;
}

static void
print_char(void **state) {
	char	buff[1024];
	FILE	*r;
	int		w;
	size_t	size;

	perror("coic");
	if ((w = open("file.txt", O_CREAT | O_TRUNC, 0644)) == -1)
		assert_false("file couldn't open");
	perror("coic");
	for (unsigned char i = 0; i < UCHAR_MAX; i++) {
		uf_print_char_fd(i, w);
	}
	close(w);
	perror("coic");
	if ((r = fopen("file.txt", "r")) == NULL) {
		assert_false("file couldn't fopen");
	}
	while (fgets(buff, sizeof(buff), r) != NULL) {
		size = strlen(buff);
		if (size > 0 && buff[size - 1] == '\n') {
			buff[size - 1] = '\0';
		}
		dprintf(2, "[%s]", buff);
	}
	// unlink("file.txt");
	fclose(r);
	close(w);
	(void)state;
}

int
main(int argc, char const** argv) {
	const struct CMUnitTest	test[] = {
		cmocka_unit_test(is_upper),
		cmocka_unit_test(is_lower),
		cmocka_unit_test(to_upper),
		cmocka_unit_test(to_lower),
		cmocka_unit_test(is_alpha),
		cmocka_unit_test(is_digit),
		cmocka_unit_test(is_print),
		cmocka_unit_test(print_char),
	};

	(void)argc;
	(void)argv;
	return (cmocka_run_group_tests(test, 0, 0));
}
