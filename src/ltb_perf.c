// Copyright (c) Kuba Szczodrzyński 2026-7-5.

#include <ltboot.h>

uint32_t ltb_perf_cpu() {
	uint32_t sum = 0;

	uint32_t start = ltb_millis();
	for (uint32_t j = 0; j < LTB_PERF_ITER; j++)
		for (uint32_t i = 0; i < LTB_PERF_WORDS; i++)
			sum += i * 3 + 1;
	uint32_t end = ltb_millis();

	(void)sum;
	return end - start;
}

uint32_t ltb_perf_mem(ltb_mem_t mem) {
	const uint32_t *addr = (void *)0xFFFFFFFF;
	// find memory region by type
	{
		ltb_mem_info_t memory[16] = {0};
		ltb_mem_info(memory);
		for (int i = 0; i < 16; i++) {
			if (memory[i].mem != mem)
				continue;
			if (memory[i].address == 0xFFFFFFFF)
				continue;
			addr = (void *)memory[i].address;
			break;
		}
		if (addr == (void *)0xFFFFFFFF)
			return 0xFFFFFFFF;
	}

	volatile uint32_t sum = 0;

	uint32_t start = ltb_millis();
	for (uint32_t j = 0; j < LTB_PERF_ITER; j++)
		for (uint32_t i = 0; i < LTB_PERF_WORDS; i++)
			sum += addr[i];
	uint32_t end = ltb_millis();

	return end - start;
}
