// Copyright (c) Kuba Szczodrzyński 2026-7-5.

#include "ln882h.h"

uint32_t ltb_millis() {
	return SystemMillis;
}

void ltb_freq_info(uint32_t *xtal_freq, uint32_t *core_freq) {
	if (xtal_freq)
		*xtal_freq = XTAL_CLOCK;
	if (core_freq)
		*core_freq = SystemCoreClock;
}

size_t ltb_mem_info(ltb_mem_info_t memory[]) {
	memory[0].mem	  = LTB_MEM_ROM;
	memory[0].address = 0x00000000;
	memory[0].length  = 128 * 1024;
	memory[1].mem	  = LTB_MEM_FLASH;
	memory[1].address = 0x10000000;
	memory[1].length  = 2048 * 1024;
	memory[2].mem	  = LTB_MEM_RAM;
	memory[2].address = 0x20000000;
	memory[2].length  = 296 * 1024;
	memory[3].mem	  = LTB_MEM_PERI;
	memory[3].address = 0x40000000;
	memory[3].length  = 0x440000;

	return 4 * sizeof(*memory);
}
