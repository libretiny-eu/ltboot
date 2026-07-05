// Copyright (c) Kuba Szczodrzyński 2026-7-5.

#pragma once

#include <stdint.h>

#define DMA_BASE		  0x20100000
#define CACHE_BASE		  0x20200000
#define SYSC_CMP_BASE	  0x40000000
#define ADC_BASE		  0x40000800
#define PWM_BASE		  0x40001000
#define EFUSE_BASE		  0x40001800
#define UART0_BASE		  0x40002000
#define UART1_BASE		  0x40003000
#define UART2_BASE		  0x40004000
#define SPI0_BASE		  0x40005000
#define SPI1_BASE		  0x40006000
#define WS2811_BASE		  0x40007000
#define I2C_BASE		  0x40008000
#define I2S_BASE		  0x40009000
#define TIMER_BASE		  0x4000A000
#define WDT_BASE		  0x4000B000
#define GPIOA_BASE		  0x4000C000
#define GPIOB_BASE		  0x4000C400
#define TRNG_BASE		  0x4000C800
#define BLE_MDM_BASE	  0x4000D000
#define MAC_PCU_REG_BASE  0x40010000
#define MAC_CE_REG_BASE	  0x40011000
#define RF_P0_BASE		  0x40012000
#define RF_P1_BASE		  0x40012400
#define SYSC_AWO_BASE	  0x40100000
#define RTC_BASE		  0x40101000
#define QSPI_BASE		  0x40200000
#define SDIO_BASE		  0x40300000
#define AES_BASE		  0x40400000
#define BLE_BASEBAND_BASE 0x40420000
#define BLE_EM_BASE		  0x40430000

typedef struct ln882h_uart_isr_t {
	uint32_t PE : 1;	   // 0  : 0
	uint32_t FE : 1;	   // 1  : 1
	uint32_t N : 1;		   // 2  : 2
	uint32_t ORE : 1;	   // 3  : 3
	uint32_t IDLE : 1;	   // 4  : 4
	uint32_t RXNE : 1;	   // 5  : 5
	uint32_t TC : 1;	   // 6  : 6
	uint32_t TXEF : 1;	   // 7  : 7
	uint32_t : 1;		   // 8  : 8
	uint32_t CTSIF : 1;	   // 9  : 9
	uint32_t CTS : 1;	   // 10 : 10
	uint32_t : 5;		   // 15 : 11
	uint32_t BUSY : 1;	   // 16 : 16
	uint32_t CMF : 1;	   // 17 : 17
	uint32_t : 1;		   // 18 : 18
	uint32_t RWU : 1;	   // 19 : 19
	uint32_t WUF : 1;	   // 20 : 20
	uint32_t RX_AFULL : 1; // 21 : 21
	uint32_t : 2;		   // 23 : 22
	uint32_t TX_FULL : 1;  // 24 : 24
	uint32_t : 7;		   // 31 : 25
} ln882h_uart_isr_t;

typedef struct {
	uint32_t BLE_GATE_EN : 1;	 // 0  : 0
	uint32_t QSPI_GATE_EN : 1;	 // 1  : 1
	uint32_t ADCC_GATE_EN : 1;	 // 2  : 2
	uint32_t I2S_GATE_EN : 1;	 // 3  : 3
	uint32_t GPIOA_GATE_EN : 1;	 // 4  : 4
	uint32_t GPIOB_GATE_EN : 1;	 // 5  : 5
	uint32_t SPI0_GATE_EN : 1;	 // 6  : 6
	uint32_t SPI1_GATE_EN : 1;	 // 7  : 7
	uint32_t WS2811_GATE_EN : 1; // 8  : 8
	uint32_t I2C0_GATE_EN : 1;	 // 9  : 9
	uint32_t UART0_GATE_EN : 1;	 // 10 : 10
	uint32_t UART1_GATE_EN : 1;	 // 11 : 11
	uint32_t UART2_GATE_EN : 1;	 // 12 : 12
	uint32_t WDT_GATE_EN : 1;	 // 13 : 13
	uint32_t TIMER_GATE_EN : 1;	 // 14 : 14
	uint32_t TIMER1_GATE_EN : 1; // 15 : 15
	uint32_t TIMER2_GATE_EN : 1; // 16 : 16
	uint32_t TIMER3_GATE_EN : 1; // 17 : 17
	uint32_t TIMER4_GATE_EN : 1; // 18 : 18
	uint32_t DBGH_GATE_EN : 1;	 // 19 : 19
	uint32_t SDIO_GATE_EN : 1;	 // 20 : 20
	uint32_t MAC_GATE_EN : 1;	 // 21 : 21
	uint32_t CACHE_GATE_EN : 1;	 // 22 : 22
	uint32_t DMA_GATE_EN : 1;	 // 23 : 23
	uint32_t RFREG_GATE_EN : 1;	 // 24 : 24
	uint32_t PWM_GATE_EN : 1;	 // 25 : 25
	uint32_t EF_GATE_EN : 1;	 // 26 : 26
	uint32_t TRNG_GATE_EN : 1;	 // 27 : 27
	uint32_t AES_GATE_EN : 1;	 // 28 : 28
	uint32_t : 3;				 // 31 : 29
} ln882h_sysc_cmp_sw_clkg_t;

typedef struct ln882h_sysc_awo_syspll_ctrl_t {
	uint32_t DIV : 5;			 // 4  : 0
	uint32_t CPAUX_IBIT : 3;	 // 7  : 5
	uint32_t VREG_BIT : 4;		 // 11 : 8
	uint32_t LF_IBIT : 3;		 // 14 : 12
	uint32_t EN : 1;			 // 15 : 15
	uint32_t CP_IBIT : 3;		 // 18 : 16
	uint32_t RST : 1;			 // 19 : 19
	uint32_t SDM_CLK_SEL : 1;	 // 20 : 20
	uint32_t RVCO_L_TEST : 1;	 // 21 : 21
	uint32_t RVCO_H_TEST : 1;	 // 22 : 22
	uint32_t SDMCLK_TEST_EN : 1; // 23 : 23
	uint32_t TEST_EN : 1;		 // 24 : 24
	uint32_t REF2X_EN : 1;		 // 25 : 25
	uint32_t : 6;				 // 31 : 26
} ln882h_sysc_awo_syspll_ctrl_t;

static volatile ln882h_sysc_cmp_sw_clkg_t *SYSC_CMP_SW_CLKG			= (void *)(SYSC_CMP_BASE + 0x10);
static volatile ln882h_sysc_awo_syspll_ctrl_t *SYSC_AWO_SYSPLL_CTRL = (void *)(SYSC_AWO_BASE + 0x70);

typedef struct ltb_uart_hw_t {
	uint32_t CR1;					// 0x0
	uint32_t CR2;					// 0x4
	uint32_t CR3;					// 0x8
	uint32_t BRR;					// 0xc
	uint32_t _1[3];					// 0x10
	volatile ln882h_uart_isr_t ISR; // 0x1c
	uint32_t ICR;					// 0x20
	volatile uint32_t RDR;			// 0x24
	volatile uint32_t TDR;			// 0x28
	uint32_t FIFO;					// 0x2c
	uint32_t MISC;					// 0x30
} ltb_uart_hw_t;
