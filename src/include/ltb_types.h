// Copyright (c) Kuba Szczodrzyński 2026-7-3.

#pragma once

typedef enum __attribute__((packed)) ltb_mem_t {
	LTB_MEM_ROM	  = 1, //!< ROM
	LTB_MEM_RAM	  = 2, //!< RAM/SRAM
	LTB_MEM_FLASH = 3, //!< Flash
	LTB_MEM_EFUSE = 4, //!< eFuse
	LTB_MEM_OTP	  = 5, //!< Flash OTP
	LTB_MEM_PERI  = 6, //!< Peripherals
} ltb_mem_t;

typedef struct __attribute__((packed)) ltb_mem_info_t {
	ltb_mem_t mem;	  //!< Memory type
	uint32_t address; //!< Address in memory space (-1 if not mapped)
	uint32_t length;  //!< Length of memory area
} ltb_mem_info_t;
