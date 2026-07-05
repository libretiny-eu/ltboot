// Copyright (c) Kuba Szczodrzyński 2026-7-3.

#pragma once

#include <stdint.h>

#include "lt_types.h"
#include "ltb_types.h"

#define LTB_CMD_MAGIC	  0x544C
#define LTB_CMD_PROTOCOL  1
#define LTB_CMD_DATA_SIZE 8192

typedef enum __attribute__((packed)) ltb_cmd_t {
	LTB_CMD_LINK_CHECK	= 0x00, // Request: (none) / Response: link_check
	LTB_CMD_VERSION		= 0x01, // Request: (none) / Response: version
	LTB_CMD_CHIP_ID		= 0x02, // Request: (none) / Response: chip_id
	LTB_CMD_SET_BAUD	= 0x03, // Request: set_baud / Response: set_baud
	LTB_CMD_INFO_MEM	= 0x08, // Request: (none) / Response: info_mem
	LTB_CMD_JUMP_APP	= 0x0F, // Request: jump_app / Response: (none)
	LTB_CMD_REG_READ	= 0x10, // Request: reg / Response: reg
	LTB_CMD_REG_WRITE	= 0x11, // Request: reg / Response: reg
	LTB_CMD_REG_UPDATE	= 0x12, // Request: reg / Response: reg
	LTB_CMD_MEM_READ	= 0x18, // Request: mem_len / Response: mem_data
	LTB_CMD_MEM_CRC32	= 0x19, // Request: mem_len / Response: mem_crc32
	LTB_CMD_MEM_WRITE	= 0x1A, // Request: mem_data / Response: (none)
	LTB_CMD_FLASH_READ	= 0x20, // Request: mem_len / Response: mem_data
	LTB_CMD_FLASH_CRC32 = 0x21, // Request: mem_len / Response: mem_crc32
	LTB_CMD_FLASH_WRITE = 0x22, // Request: mem_data / Response: (none)
	LTB_CMD_FLASH_ERASE = 0x23, // Request: mem_len / Response: (none)
} ltb_cmd_t;

typedef enum __attribute__((packed)) ltb_err_t {
	LTB_ERR_OK = 0,
	LTB_ERR_HDR_TOO_SHORT,
	LTB_ERR_BAD_MAGIC,
	LTB_ERR_DATA_TOO_LONG,
	LTB_ERR_DATA_TOO_SHORT,
	LTB_ERR_BAD_CRC,
	LTB_ERR_BAD_CMD,
	LTB_ERR_BAD_DATA,
	LTB_ERR_NO_RESP = 100,
	LTB_ERR_NO_DATA,
} ltb_err_t;

typedef struct __attribute__((packed)) ltb_cmd_hdr_t {
	uint16_t magic;
	uint16_t crc16; //!< CRC16 of len,cmd,err and data
	uint16_t len;
	ltb_cmd_t cmd;
	ltb_err_t err;
} ltb_cmd_hdr_t;

typedef union __attribute__((packed)) ltb_packet_t {
	struct {
		ltb_cmd_hdr_t hdr;
		uint8_t data[LTB_CMD_DATA_SIZE];
	};

	struct __attribute__((packed)) {
		ltb_cmd_hdr_t hdr;
		uint8_t protocol;
		uint32_t data_size;
	} link_check;

	struct {
		ltb_cmd_hdr_t hdr;
		char banner[];
	} version;

	struct {
		ltb_cmd_hdr_t hdr;
		lt_cpu_family_t family;
		lt_cpu_model_t model;
	} chip_id;

	struct {
		ltb_cmd_hdr_t hdr;
		uint32_t baud;
	} set_baud;

	struct __attribute__((packed)) {
		ltb_cmd_hdr_t hdr;
		ltb_mem_info_t memory[];
	} info_mem;

	struct {
		ltb_cmd_hdr_t hdr;
		void *address;
		uint32_t mask;
		uint32_t value;
	} reg;

	struct {
		ltb_cmd_hdr_t hdr;
		void *address;
		uint32_t length;
	} mem_len;

	struct {
		ltb_cmd_hdr_t hdr;
		void *address;
		uint8_t data[];
	} mem_data;

	struct {
		ltb_cmd_hdr_t hdr;
		void *address;
		uint32_t length;
		uint32_t crc32;
	} mem_crc32;
} ltb_packet_t;
