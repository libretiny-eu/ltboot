// Copyright (c) Kuba Szczodrzyński 2026-7-2.

#pragma once

#include <errno.h>
#include <memory.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/unistd.h>

#include <git_version.h>

#include "lt_types.h"
#include "ltb_cmd.h"
#include "ltb_types.h"

#define STRINGIFY(x)	   #x
#define STRINGIFY_MACRO(x) STRINGIFY(x)
#define BIT(x)			   (1 << (x))

#define LTB_BANNER_STR "ltboot " GIT_VERSION " on " STRINGIFY_MACRO(LTB_PORT) ", compiled at " __DATE__ " " __TIME__

#define LTB_MEM(addr)  *((volatile uint32_t *)(addr))
#define LTB_PERF_ITER  (500)
#define LTB_PERF_WORDS (4096)

typedef struct ltb_uart_hw_t ltb_uart_hw_t;
extern ltb_uart_hw_t *UART_DL;
extern ltb_uart_hw_t *UART_LOG;

// main.c
int main(int argc, char *argv[]);

// port/*/*.c
void ltb_port_init();

// port/*/ltb_core.c
uint32_t ltb_millis();
void ltb_freq_info(uint32_t *xtal_freq, uint32_t *core_freq);
size_t ltb_mem_info(ltb_mem_info_t memory[]);

// ltb_crc.c (or port/*/ltb_crc.c)
uint16_t ltb_crc16(const void *buf, size_t len); //!< CRC-16/XMODEM
uint32_t ltb_crc32(const void *buf, size_t len); //!< CRC-32/ISO-HDLC

// ltb_dl_mode.c
void ltb_dl_mode(ltb_uart_hw_t *uart);

// ltb_perf.c
uint32_t ltb_perf_cpu();
uint32_t ltb_perf_mem(ltb_mem_t mem);

// port/*/ltb_uart.c
void ltb_uart_init(ltb_uart_hw_t *hw, uint32_t baud);
void ltb_uart_putchar(ltb_uart_hw_t *hw, char ch);
char ltb_uart_getchar(ltb_uart_hw_t *hw);
void ltb_uart_write(ltb_uart_hw_t *hw, const void *buf, size_t len);
size_t ltb_uart_read(ltb_uart_hw_t *hw, void *buf, size_t len, uint32_t timeout);
void ltb_uart_flush(ltb_uart_hw_t *hw);
