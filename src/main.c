// Copyright (c) Kuba Szczodrzyński 2026-7-2.

#include <ltboot.h>

int main(int argc, char *argv[]) {
	ltb_port_init();
	ltb_uart_init(UART_LOG, 115200);
	ltb_uart_init(UART_DL, 115200);
	ltb_dl_mode(UART_DL);
}
