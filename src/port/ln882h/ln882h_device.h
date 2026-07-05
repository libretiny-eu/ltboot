// Copyright (c) Kuba Szczodrzyński 2026-7-3.

#pragma once

typedef enum IRQn {
	Reset_IRQn			  = -15,
	NonMaskableInt_IRQn	  = -14,
	HardFault_IRQn		  = -13,
	MemoryManagement_IRQn = -12,
	BusFault_IRQn		  = -11,
	UsageFault_IRQn		  = -10,
	SVCall_IRQn			  = -5,
	DebugMonitor_IRQn	  = -4,
	PendSV_IRQn			  = -2,
	SysTick_IRQn		  = -1,
	WDT_IRQn			  = 0,
	EXT_IRQn			  = 1,
	RTC_IRQn			  = 2,
	RFSLP_IRQn			  = 3,
	MAC_IRQn			  = 4,
	BLE_WAKE_IRQn		  = 5,
	BLE_ERR_IRQn		  = 6,
	BLE_MAC_IRQn		  = 7,
	DMA_IRQn			  = 8,
	QSPI_IRQn			  = 9,
	SDIO_F1_IRQn		  = 10,
	SDIO_F2_IRQn		  = 11,
	SDIO_F3_IRQn		  = 12,
	CM4_FPIXC_IRQn		  = 13,
	CM4_FPOFC_IRQn		  = 14,
	CM4_FPUFC_IRQn		  = 15,
	CM4_FPIOC_IRQn		  = 16,
	CM4_FPDZC_IRQn		  = 17,
	CM4_FPIDC_IRQn		  = 18,
	I2C_IRQn			  = 19,
	SPI0_IRQn			  = 20,
	SPI1_IRQn			  = 21,
	UART0_IRQn			  = 22,
	UART1_IRQn			  = 23,
	UART2_IRQn			  = 24,
	ADC_IRQn			  = 25,
	WS_IRQn				  = 26,
	I2S_IRQn			  = 27,
	GPIOA_IRQn			  = 28,
	GPIOB_IRQn			  = 29,
	TIMER0_IRQn			  = 30,
	TIMER1_IRQn			  = 31,
	TIMER2_IRQn			  = 32,
	TIMER3_IRQn			  = 33,
	ADV_TIMER_IRQn		  = 34,
	AES_IRQn			  = 35,
	TRNG_IRQn			  = 36,
	PAOTD_IRQn			  = 37,
} IRQn_Type;

#define __CM4_REV			   0x0201U /*!< Core Revision r2p1 */
#define __MPU_PRESENT		   1U	   /*!< Set to 1 if MPU is present */
#define __VTOR_PRESENT		   1U	   /*!< Set to 1 if VTOR is present */
#define __NVIC_PRIO_BITS	   3U	   /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig 0U	   /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT		   1U	   /*!< Set to 1 if FPU is present */
#define __FPU_DP			   0U	   /*!< Set to 1 if FPU is double precision FPU (default is single precision FPU) */
#define __ICACHE_PRESENT	   0U	   /*!< Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT	   0U	   /*!< Set to 1 if D-Cache is present */
#define __DTCM_PRESENT		   0U	   /*!< Set to 1 if DTCM is present */

#include <core_cm4.h>

typedef void (*Vector_Handler)();

typedef struct Vector_Table {
	void *Initial_SP;
	Vector_Handler Reset;
	Vector_Handler NMI;
	Vector_Handler HardFault;
	Vector_Handler MemManage;
	Vector_Handler BusFault;
	Vector_Handler UsageFault;
	unsigned long : 32;
	unsigned long : 32;
	unsigned long : 32;
	unsigned long : 32;
	Vector_Handler SVC;
	Vector_Handler DebugMon;
	unsigned long : 32;
	Vector_Handler PendSV;
	Vector_Handler SysTick_;
	Vector_Handler IRQ[38];
} Vector_Table;
