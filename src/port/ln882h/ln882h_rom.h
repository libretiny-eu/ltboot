// Copyright (c) Kuba Szczodrzyński 2026-7-5.

#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint32_t baudrate;
	uint16_t word_len;
	uint16_t stop_bits;
	uint16_t parity;
	uint16_t over_sampl;
} uart_init_t_def;

static void (*const LL_SYSCON_CPUResetReqMask)(uint8_t)			   = (void *)0x16A5;
static void (*const LL_SYSCON_SelectSysClkSrc)(uint8_t)			   = (void *)0x1719;
static void (*const LL_SYSCON_SetHclkDivision)(uint8_t)			   = (void *)0x1725;
static void (*const LL_SYSCON_SetPclk0Division)(uint8_t)		   = (void *)0x1749;
static uint16_t (*const crc16_ccitt)(const void *, size_t)		   = (void *)0x4039;
static uint32_t (*const ln_crc32_signle_cal)(const void *, size_t) = (void *)0x50F9;
static void (*const hal_uart_en)(void *, bool)					   = (void *)0x6965;
static void (*const hal_uart_init)(void *, uart_init_t_def *)	   = (void *)0x698B;
static void (*const uart_io_pin_request)(uint32_t *)			   = (void *)0x69E5;
static void (*const hal_uart_rx_mode_en)(void *, bool)			   = (void *)0x6C29;
static void (*const hal_uart_tx_mode_en)(void *, bool)			   = (void *)0x6C41;
