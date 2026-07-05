// Copyright (c) Kuba Szczodrzyński 2026-7-3.

#include <ltboot.h>

static ltb_packet_t packet;

static ltb_err_t ltb_dl_cmd_recv(ltb_uart_hw_t *uart);
static void ltb_dl_cmd_send(ltb_uart_hw_t *uart, ltb_err_t err);
static ltb_err_t ltb_dl_cmd_handle(ltb_uart_hw_t *uart);

__attribute__((noreturn)) void ltb_dl_mode(ltb_uart_hw_t *uart) {
	while (1) {
		// receive command from UART
		ltb_err_t err = ltb_dl_cmd_recv(uart);
		// if nothing received, continue silently
		if (err == LTB_ERR_NO_DATA)
			continue;

		// if no receive error, handle the command
		if (err == LTB_ERR_OK)
			err = ltb_dl_cmd_handle(uart);

		// send a response if not requested otherwise
		if (err != LTB_ERR_NO_RESP)
			ltb_dl_cmd_send(uart, err);
	}
}

static ltb_err_t ltb_dl_cmd_recv(ltb_uart_hw_t *uart) {
	// clear cmd as it won't be updated in ltb_dl_mode()
	packet.hdr.cmd = 0;

	// read header from UART
	size_t read = ltb_uart_read(uart, &packet.hdr, sizeof(packet.hdr), 200);
	if (read == 0)
		return LTB_ERR_NO_DATA;
	if (read != sizeof(packet.hdr))
		return LTB_ERR_HDR_TOO_SHORT;
	if (packet.hdr.magic != LTB_CMD_MAGIC)
		return LTB_ERR_BAD_MAGIC;
	if (packet.hdr.len > sizeof(packet))
		return LTB_ERR_DATA_TOO_LONG;

	// read data payload from UART
	read = ltb_uart_read(uart, packet.data, packet.hdr.len - sizeof(packet.hdr), 1000);
	if (read != packet.hdr.len - sizeof(packet.hdr))
		return LTB_ERR_DATA_TOO_SHORT;

	// calculate CRC16
	uint16_t crc16 = ltb_crc16(
		/* buf= */ &packet.hdr.len,
		/* len= */ packet.hdr.len - sizeof(packet.hdr.magic) - sizeof(packet.hdr.crc16)
	);
	if (packet.hdr.crc16 != crc16)
		return LTB_ERR_BAD_CRC;

	return LTB_ERR_OK;
}

static void ltb_dl_cmd_send(ltb_uart_hw_t *uart, ltb_err_t err) {
	// fixup response magic
	packet.hdr.magic = LTB_CMD_MAGIC;
	// assign error code to response
	packet.hdr.err = err;
	// clear response data in case of errors
	if (err != LTB_ERR_OK)
		packet.hdr.len = sizeof(packet.hdr);

	// calculate CRC16
	uint16_t crc16 = ltb_crc16(
		/* buf= */ &packet.hdr.len,
		/* len= */ packet.hdr.len - sizeof(packet.hdr.magic) - sizeof(packet.hdr.crc16)
	);
	packet.hdr.crc16 = crc16;

	// write response to UART
	ltb_uart_write(uart, &packet, packet.hdr.len);
}

static ltb_err_t ltb_dl_cmd_handle(ltb_uart_hw_t *uart) {
	switch (packet.hdr.cmd) {
		case LTB_CMD_LINK_CHECK: {
			// Request: (none) / Response: link_check
			packet.link_check.protocol	= LTB_CMD_PROTOCOL;
			packet.link_check.data_size = LTB_CMD_DATA_SIZE;
			packet.hdr.len				= sizeof(packet.link_check);
			return LTB_ERR_OK;
		}

		case LTB_CMD_VERSION: {
			// Request: (none) / Response: version
			strcpy(packet.version.banner, LTB_BANNER_STR);
			packet.hdr.len = sizeof(packet.version) + strlen(packet.version.banner);
			return LTB_ERR_OK;
		}

		case LTB_CMD_CHIP_ID: {
			// Request: (none) / Response: chip_id
			// TODO
			break;
		}

		case LTB_CMD_SET_BAUD: {
			if (packet.hdr.len < sizeof(packet.set_baud))
				return LTB_ERR_DATA_TOO_SHORT;
			// Request: set_baud / Response: set_baud
			// send a successful response immediately
			packet.hdr.len = sizeof(packet.set_baud);
			ltb_dl_cmd_send(uart, LTB_ERR_OK);
			// wait for the transmission to finish
			ltb_uart_flush(uart);
			// reinitialize UART
			ltb_uart_init(uart, packet.set_baud.baud);
			return LTB_ERR_NO_RESP;
		}

		case LTB_CMD_INFO_MEM: {
			// Request: (none) / Response: info_mem
			packet.hdr.len = sizeof(packet.info_mem) + ltb_mem_info(packet.info_mem.memory);
			return LTB_ERR_OK;
		}

		case LTB_CMD_INFO_CLK: {
			// Request: (none) / Response: info_clk
			uint32_t xtal_freq, core_freq;
			ltb_freq_info(&xtal_freq, &core_freq);
			packet.info_clk.xtal_freq = xtal_freq;
			packet.info_clk.core_freq = core_freq;
			packet.hdr.len			  = sizeof(packet.info_clk);
			return LTB_ERR_OK;
		}

		case LTB_CMD_INFO_PERF: {
			// Request: (none) / Response: info_perf
			packet.info_perf.iter  = LTB_PERF_ITER;
			packet.info_perf.words = LTB_PERF_WORDS;
			// run the benchmark
			packet.info_perf.cpu_ms	  = ltb_perf_cpu();
			packet.info_perf.rom_ms	  = ltb_perf_mem(LTB_MEM_ROM);
			packet.info_perf.ram_ms	  = ltb_perf_mem(LTB_MEM_RAM);
			packet.info_perf.flash_ms = ltb_perf_mem(LTB_MEM_FLASH);
			packet.hdr.len			  = sizeof(packet.info_perf);
			return LTB_ERR_OK;
		}

		case LTB_CMD_JUMP_APP: {
			// Request: jump_app / Response: (none)
			// TODO
			break;
		}

		case LTB_CMD_REBOOT: {
			// Request: (none) / Response: (none)
			// TODO
			break;
		}

		case LTB_CMD_REG_READ: {
			// Request: reg / Response: reg
			if (packet.hdr.len < sizeof(packet.reg))
				return LTB_ERR_DATA_TOO_SHORT;
			packet.reg.value = LTB_MEM(packet.reg.address);
			return LTB_ERR_OK;
		}

		case LTB_CMD_REG_WRITE: {
			// Request: reg / Response: reg
			if (packet.hdr.len < sizeof(packet.reg))
				return LTB_ERR_DATA_TOO_SHORT;
			LTB_MEM(packet.reg.address) = packet.reg.value;
			packet.reg.value			= LTB_MEM(packet.reg.address);
			return LTB_ERR_OK;
		}

		case LTB_CMD_REG_UPDATE: {
			// Request: reg / Response: reg
			if (packet.hdr.len < sizeof(packet.reg))
				return LTB_ERR_DATA_TOO_SHORT;
			LTB_MEM(packet.reg.address) =
				(LTB_MEM(packet.reg.address) & ~packet.reg.mask) | (packet.reg.value & packet.reg.mask);
			packet.reg.value = LTB_MEM(packet.reg.address);
			return LTB_ERR_OK;
		}

		case LTB_CMD_MEM_READ: {
			// Request: mem_len / Response: mem_data
			if (packet.hdr.len < sizeof(packet.mem_len))
				return LTB_ERR_DATA_TOO_SHORT;
			if (packet.mem_len.length > sizeof(packet.data))
				return LTB_ERR_DATA_TOO_LONG;
			void *src	 = packet.mem_len.address;
			void *dst	 = packet.mem_data.data;
			uint32_t len = packet.mem_len.length;
			// process command
			memcpy(dst, src, len);
			packet.mem_data.address = src;
			packet.hdr.len			= sizeof(packet.mem_data) + len;
			return LTB_ERR_OK;
		}

		case LTB_CMD_MEM_CRC32: {
			// Request: mem_len / Response: mem_crc32
			if (packet.hdr.len < sizeof(packet.mem_len))
				return LTB_ERR_DATA_TOO_SHORT;
			void *src	 = packet.mem_len.address;
			uint32_t len = packet.mem_len.length;
			// process command
			packet.mem_crc32.address = src;
			packet.mem_crc32.length	 = len;
			packet.mem_crc32.crc32	 = ltb_crc32(src, len);
			packet.hdr.len			 = sizeof(packet.mem_crc32);
			return LTB_ERR_OK;
		}

		case LTB_CMD_MEM_WRITE: {
			// Request: mem_data / Response: (none)
			if (packet.hdr.len < sizeof(packet.mem_data))
				return LTB_ERR_DATA_TOO_SHORT;
			const void *src = packet.mem_data.data;
			void *dst		= packet.mem_data.address;
			uint32_t len	= packet.hdr.len - sizeof(packet.mem_data);
			// process command
			memcpy(dst, src, len);
			packet.hdr.len = sizeof(packet.hdr);
			return LTB_ERR_OK;
		}

		case LTB_CMD_FLASH_READ: {
			// Request: mem_len / Response: mem_data
			// TODO
			if (packet.hdr.len < sizeof(packet.mem_len))
				return LTB_ERR_DATA_TOO_SHORT;
			if (packet.mem_len.length > sizeof(packet.data))
				return LTB_ERR_DATA_TOO_LONG;
			break;
		}

		case LTB_CMD_FLASH_CRC32: {
			// Request: mem_len / Response: mem_crc32
			// TODO
			if (packet.hdr.len < sizeof(packet.mem_len))
				return LTB_ERR_DATA_TOO_SHORT;
			packet.hdr.len = sizeof(packet.mem_crc32);
			break;
		}

		case LTB_CMD_FLASH_WRITE: {
			// Request: mem_data / Response: (none)
			// TODO
			if (packet.hdr.len < sizeof(packet.mem_data))
				return LTB_ERR_DATA_TOO_SHORT;
			packet.hdr.len = sizeof(packet.hdr);
			break;
		}

		case LTB_CMD_FLASH_ERASE: {
			// Request: mem_len / Response: (none)
			// TODO
			if (packet.hdr.len < sizeof(packet.mem_len))
				return LTB_ERR_DATA_TOO_SHORT;
			packet.hdr.len = sizeof(packet.hdr);
			break;
		}
	}

	return LTB_ERR_BAD_CMD;
}
