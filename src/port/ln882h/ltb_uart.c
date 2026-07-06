// Copyright (c) Kuba Szczodrzyński 2026-7-5.

#include "ln882h.h"

#define FUNC_UART0_TX 2
#define FUNC_UART0_RX 3
#define FUNC_UART1_TX 6
#define FUNC_UART1_RX 7
#define FUNC_UART2_TX 8
#define FUNC_UART2_RX 9

void ltb_uart_init(ltb_uart_hw_t *hw, uint32_t baud) {
	switch ((uintptr_t)hw) {
		case UART0_BASE:
			SYSC_CMP_SW_CLKG->UART0_GATE_EN = true;
			break;
		case UART1_BASE:
			SYSC_CMP_SW_CLKG->UART1_GATE_EN = true;
			break;
		case UART2_BASE:
			SYSC_CMP_SW_CLKG->UART2_GATE_EN = true;
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

	switch ((uintptr_t)hw) {
		case UART0_BASE:
			SYSC_CMP_FUNC_ISEL_0->IO02_SEL = FUNC_UART0_TX; // FULLMUX2 (GPIOA2)
			SYSC_CMP_FUNC_ISEL_0->IO03_SEL = FUNC_UART0_RX; // FULLMUX3 (GPIOA3)
			SYSC_CMP_FUNC_EN->IEN |= (1 << 3) | (1 << 2);
			break;
		case UART1_BASE:
			SYSC_CMP_FUNC_ISEL_4->IO19_SEL = FUNC_UART1_TX; // FULLMUX19 (GPIOB9)
			SYSC_CMP_FUNC_ISEL_4->IO18_SEL = FUNC_UART1_RX; // FULLMUX18 (GPIOB8)
			SYSC_CMP_FUNC_EN->IEN |= (1 << 19) | (1 << 18);
			break;
		case UART2_BASE:
			SYSC_CMP_FUNC_ISEL_3->IO15_SEL = FUNC_UART2_TX; // FULLMUX15 (GPIOB5)
			SYSC_CMP_FUNC_ISEL_4->IO16_SEL = FUNC_UART2_RX; // FULLMUX16 (GPIOB6)
			SYSC_CMP_FUNC_EN->IEN |= (1 << 16) | (1 << 15);
			break;
	}
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
