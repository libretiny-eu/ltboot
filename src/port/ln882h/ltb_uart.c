// Copyright (c) Kuba Szczodrzyński 2026-7-5.

#include "ln882h.h"

void ltb_uart_init(ltb_uart_hw_t *hw, uint32_t baud) {
	uint32_t port_id;
	switch ((uintptr_t)hw) {
		case UART0_BASE:
			SYSC_CMP_SW_CLKG->UART0_GATE_EN = true, port_id = 0;
			break;
		case UART1_BASE:
			SYSC_CMP_SW_CLKG->UART1_GATE_EN = true, port_id = 1;
			break;
		case UART2_BASE:
			SYSC_CMP_SW_CLKG->UART2_GATE_EN = true, port_id = 2;
			break;
		default:
			return;
	}

	for (volatile int i = 0; i < 20; i++)
		__NOP();

	uart_init_t_def init = {
		.baudrate	= baud,
		.word_len	= 0, // UART_WORD_LEN_8
		.stop_bits	= 0, // UART_STOP_BITS_1
		.parity		= 2, // UART_PARITY_NONE
		.over_sampl = 1, // UART_OVER_SAMPL_8
	};
	hal_uart_init(hw, &init);
	hal_uart_rx_mode_en(hw, true);
	hal_uart_tx_mode_en(hw, true);
	hal_uart_en(hw, true);

	// ROM code uses:
	// - GPIOA2 = UART0_TX
	// - GPIOA3 = UART0_RX
	// - GPIOA9 = UART1_TX
	// - GPIOA8 = UART1_RX
	uart_io_pin_request(&port_id);
}

void ltb_uart_putchar(ltb_uart_hw_t *hw, char ch) {
	while (hw->ISR.TX_FULL) {}
	hw->TDR = ch;
}

char ltb_uart_getchar(ltb_uart_hw_t *hw) {
	while (!hw->ISR.RXNE) {}
	return hw->RDR;
}

void ltb_uart_write(ltb_uart_hw_t *hw, const void *buf, size_t len) {
	const uint8_t *buf8 = buf;
	while (len--) {
		ltb_uart_putchar(hw, *buf8++);
	}
}

size_t ltb_uart_read(ltb_uart_hw_t *hw, void *buf, size_t len, uint32_t timeout) {
	size_t read	 = 0;
	uint32_t end = timeout ? ltb_millis() + timeout : 0;

	uint8_t *buf8 = buf;
	while (len--) {
		while (!hw->ISR.RXNE) {
			if (timeout && ltb_millis() > end)
				return read;
		}
		*buf8++ = hw->RDR;
		read++;
	}
	return read;
}

void ltb_uart_flush(ltb_uart_hw_t *hw) {
	// flush TX
	while (!hw->ISR.TC) {}
	// flush RX
	while (hw->ISR.RXNE) {
		(void)hw->RDR;
	}
}
