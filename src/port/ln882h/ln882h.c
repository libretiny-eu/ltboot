// Copyright (c) Kuba Szczodrzyński 2026-7-2.

#include "ln882h.h"

ltb_uart_hw_t *UART_DL	= (void *)UART0_BASE;
ltb_uart_hw_t *UART_LOG = (void *)UART1_BASE;

uint32_t SystemAPB0Clock = 0;
uint32_t SystemAHBClock	 = 0;
uint32_t SystemCoreClock = 0;
uint32_t SystemMillis	 = 0;

void ltb_port_init() {
	uint32_t clk_src  = 1; // CLK_SRC_PLL
	uint32_t pll_mul  = 4;
	uint32_t ahb_div  = 1;
	uint32_t apb0_div = 4;

	// configure clock dividers
	LL_SYSCON_SelectSysClkSrc(clk_src);
	SYSC_AWO_SYSPLL_CTRL->DIV = pll_mul * 2;
	LL_SYSCON_SetHclkDivision(ahb_div);	  // CLK_HCLK_NO_DIV (AHB_DIV)
	LL_SYSCON_SetPclk0Division(apb0_div); // CLK_PCLK0_4_DIV (APB0_DIV)
	LL_SYSCON_CPUResetReqMask(0);

	// calculate resulting clocks
	SystemAPB0Clock = XTAL_CLOCK * pll_mul / ahb_div / apb0_div; // 40 MHz
	SystemAHBClock	= XTAL_CLOCK * pll_mul / ahb_div;			 // 160 MHz
	SystemCoreClock = XTAL_CLOCK * pll_mul;						 // 160 MHz

	// enable SysTick interrupt at 1000 Hz
	SysTick->LOAD = (SystemCoreClock / 1000) - 1UL;
	SysTick->CTRL = (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);

	// set interrupt priorities
	__NVIC_SetPriorityGrouping(4);
	NVIC_SetPriority(SysTick_IRQn, 1);
	NVIC_SetPriority(UART0_IRQn, 4);
	NVIC_SetPriority(UART1_IRQn, 4);
	__enable_irq();
}

void SysTick_Handler() {
	SystemMillis++;
}
