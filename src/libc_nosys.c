// Copyright (c) Kuba Szczodrzyński 2026-7-3.

#include <ltboot.h>

int _isatty(int fd) {
	if (fd >= STDIN_FILENO && fd <= STDERR_FILENO)
		return 1;
	errno = ENOTSUP;
	return -1;
}

ssize_t _read(int fd, void *buf, size_t nbytes) {
	errno = ENOTSUP;
	return -1;
}

ssize_t _write(int fd, const void *buf, size_t n) {
	ltb_uart_write(UART_LOG, buf, n);
	return (ssize_t)n;
}
