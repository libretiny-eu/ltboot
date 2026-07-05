// Copyright (c) Kuba Szczodrzyński 2026-7-2.

#pragma once

#include <ltboot.h>

#include "ln882h_device.h"
#include "ln882h_peri.h"
#include "ln882h_rom.h"

typedef struct boot_header_t {
	const struct boot_header_t *image_addr;
	uint16_t bin_length;
	uint16_t crc_offset;
	uint32_t crc_value;
	const Vector_Table *vector_addr;
	uint32_t crp_flag;
	uint32_t crc;
	uint32_t : 32;
	uint32_t : 32;
	char info[128];
} boot_header_t;

#define XTAL_CLOCK (40000000) // 40 MHz

// ln882h.c
extern uint32_t SystemAPB0Clock;
extern uint32_t SystemAHBClock;
extern uint32_t SystemCoreClock;
extern uint32_t SystemMillis;

// ln882h.lds
extern uint32_t __text_sram_load[];
extern uint32_t __text_sram_start[];
extern uint32_t __text_sram_end[];
extern uint32_t __data_load[];
extern uint32_t __data_start[];
extern uint32_t __data_end[];
extern uint32_t __bss_start[];
extern uint32_t __bss_end[];
extern uint32_t __stack_limit[];
extern uint32_t __stack_top[];
