// Copyright (c) Kuba Szczodrzyński 2026-7-2.

#include "ln882h.h"

void Reset_Handler(void);
void Default_Handler(void);

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

void WDT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void EXT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RTC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void RFSLP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void MAC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void BLE_WAKE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void BLE_ERR_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void BLE_MAC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void DMA_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void QSPI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SDIO_F1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SDIO_F2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SDIO_F3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CM4_FPIXC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CM4_FPOFC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CM4_FPUFC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CM4_FPIOC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CM4_FPDZC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void CM4_FPIDC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2C_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void UART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void WS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void I2S_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOA_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void GPIOB_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMER0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMER1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMER2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TIMER3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void ADV_TIMER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void AES_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void TRNG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
void PAOTD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

__attribute__((section(".vectors"))) const Vector_Table __Vectors = {
	.Initial_SP			 = __stack_top,
	.Reset				 = Reset_Handler,
	.NMI				 = NMI_Handler,
	.HardFault			 = HardFault_Handler,
	.MemManage			 = MemManage_Handler,
	.BusFault			 = BusFault_Handler,
	.UsageFault			 = UsageFault_Handler,
	.SVC				 = SVC_Handler,
	.DebugMon			 = DebugMon_Handler,
	.PendSV				 = PendSV_Handler,
	.SysTick_			 = SysTick_Handler,
	.IRQ[WDT_IRQn]		 = WDT_IRQHandler,
	.IRQ[EXT_IRQn]		 = EXT_IRQHandler,
	.IRQ[RTC_IRQn]		 = RTC_IRQHandler,
	.IRQ[RFSLP_IRQn]	 = RFSLP_IRQHandler,
	.IRQ[MAC_IRQn]		 = MAC_IRQHandler,
	.IRQ[BLE_WAKE_IRQn]	 = BLE_WAKE_IRQHandler,
	.IRQ[BLE_ERR_IRQn]	 = BLE_ERR_IRQHandler,
	.IRQ[BLE_MAC_IRQn]	 = BLE_MAC_IRQHandler,
	.IRQ[DMA_IRQn]		 = DMA_IRQHandler,
	.IRQ[QSPI_IRQn]		 = QSPI_IRQHandler,
	.IRQ[SDIO_F1_IRQn]	 = SDIO_F1_IRQHandler,
	.IRQ[SDIO_F2_IRQn]	 = SDIO_F2_IRQHandler,
	.IRQ[SDIO_F3_IRQn]	 = SDIO_F3_IRQHandler,
	.IRQ[CM4_FPIXC_IRQn] = CM4_FPIXC_IRQHandler,
	.IRQ[CM4_FPOFC_IRQn] = CM4_FPOFC_IRQHandler,
	.IRQ[CM4_FPUFC_IRQn] = CM4_FPUFC_IRQHandler,
	.IRQ[CM4_FPIOC_IRQn] = CM4_FPIOC_IRQHandler,
	.IRQ[CM4_FPDZC_IRQn] = CM4_FPDZC_IRQHandler,
	.IRQ[CM4_FPIDC_IRQn] = CM4_FPIDC_IRQHandler,
	.IRQ[I2C_IRQn]		 = I2C_IRQHandler,
	.IRQ[SPI0_IRQn]		 = SPI0_IRQHandler,
	.IRQ[SPI1_IRQn]		 = SPI1_IRQHandler,
	.IRQ[UART0_IRQn]	 = UART0_IRQHandler,
	.IRQ[UART1_IRQn]	 = UART1_IRQHandler,
	.IRQ[UART2_IRQn]	 = UART2_IRQHandler,
	.IRQ[ADC_IRQn]		 = ADC_IRQHandler,
	.IRQ[WS_IRQn]		 = WS_IRQHandler,
	.IRQ[I2S_IRQn]		 = I2S_IRQHandler,
	.IRQ[GPIOA_IRQn]	 = GPIOA_IRQHandler,
	.IRQ[GPIOB_IRQn]	 = GPIOB_IRQHandler,
	.IRQ[TIMER0_IRQn]	 = TIMER0_IRQHandler,
	.IRQ[TIMER1_IRQn]	 = TIMER1_IRQHandler,
	.IRQ[TIMER2_IRQn]	 = TIMER2_IRQHandler,
	.IRQ[TIMER3_IRQn]	 = TIMER3_IRQHandler,
	.IRQ[ADV_TIMER_IRQn] = ADV_TIMER_IRQHandler,
	.IRQ[AES_IRQn]		 = AES_IRQHandler,
	.IRQ[TRNG_IRQn]		 = TRNG_IRQHandler,
	.IRQ[PAOTD_IRQn]	 = PAOTD_IRQHandler,
};

// Disable CRC calculation by setting .bin_length and .crc_offset to 0x0.
// The expected value calculated by ROM's ln_crc32_signle_cal() is then also 0x0.
__attribute__((section(".boot_header"))) const boot_header_t boot_header = {
	.image_addr	 = &boot_header,
	.bin_length	 = 0,
	.crc_offset	 = 0,
	.crc_value	 = 0x0,
	.vector_addr = &__Vectors,
	.crp_flag	 = 0x0,
	.crc		 = 0x0,
	.info		 = LTB_BANNER_STR,
};

void Reset_Handler() {
	memcpy(__text_sram_start, __text_sram_load, (uintptr_t)__text_sram_end - (uintptr_t)__text_sram_start);
	memcpy(__data_start, __data_load, (uintptr_t)__data_end - (uintptr_t)__data_start);
	memset(__bss_start, 0, (uintptr_t)__bss_end - (uintptr_t)__bss_start);

#if defined(__VTOR_PRESENT) && (__VTOR_PRESENT == 1U)
	__DMB();
	SCB->VTOR = (uint32_t)&__Vectors;
	__DSB();
#endif

#if defined(__FPU_USED) && (__FPU_USED == 1U)
	SCB->CPACR |=
		((3U << 10U * 2U) | /* enable CP10 Full Access */
		 (3U << 11U * 2U)); /* enable CP11 Full Access */
#endif

#if defined(SCB_SHCSR_MEMFAULTENA_Msk)
	SCB->SHCSR |= SCB_SHCSR_MEMFAULTENA_Msk;
#endif
#if defined(SCB_SHCSR_BUSFAULTENA_Msk)
	SCB->SHCSR |= SCB_SHCSR_BUSFAULTENA_Msk;
#endif
#if defined(SCB_SHCSR_USGFAULTENA_Msk)
	SCB->SHCSR |= SCB_SHCSR_USGFAULTENA_Msk;
#endif

#if defined(SCB_CCR_DIV_0_TRP_Msk)
	SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
#endif

#ifdef UNALIGNED_SUPPORT_DISABLE
	SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

	main(0, NULL);
}

void Default_Handler(void) {
	while (1)
		;
}
