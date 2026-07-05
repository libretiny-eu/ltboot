OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)

ENTRY(Reset_Handler)

MEMORY
{
	ROM        (rx)  : ORIGIN = 0x00000000, LENGTH = 128K
	FLASH_BOOT (rx)  : ORIGIN = 0x10000000, LENGTH = 24K
	FLASH_APP  (rx)  : ORIGIN = 0x10007000, LENGTH = 1200K
	SRAM       (rwx) : ORIGIN = 0x20000000, LENGTH = 295K
	RETENTION  (rwx) : ORIGIN = 0x20049C00, LENGTH = 1K
}

STACK_SIZE = 0x00001000;

#if LN882H_FLASH
#define SRAM_AT_FLASH SRAM AT> FLASH_APP
#define FLASH_OR_SRAM FLASH_APP
#elif LN882H_SRAM
#define SRAM_AT_FLASH SRAM
#define FLASH_OR_SRAM SRAM
#else
#error "Missing flag: LN882H_FLASH or LN882H_SRAM"
#endif

SECTIONS
{
	.text.sram :
	{
		PROVIDE(__text_sram_load = LOADADDR(.text.sram));
		PROVIDE(__text_sram_start = .);

		KEEP(*(.boot_header))
		. = ALIGN(0x100);
		KEEP(*(.vectors))

		PROVIDE(__text_sram_end = .);
	} > SRAM_AT_FLASH

	.text :
	{
		PROVIDE(__text_start = .);

		*(.text*)

		KEEP(*(.init))
		KEEP(*(.fini))

		/* .ctors */
		*crtbegin.o(.ctors)
		*crtbegin?.o(.ctors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
		*(SORT(.ctors.*))
		*(.ctors)

		/* .dtors */
		*crtbegin.o(.dtors)
		*crtbegin?.o(.dtors)
		*(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
		*(SORT(.dtors.*))
		*(.dtors)

		KEEP(*(.eh_frame*))

		PROVIDE(__text_end = .);
	} > FLASH_OR_SRAM

	.rodata :
	{
		PROVIDE(__rodata_start = .);
		*(.rodata*)
		PROVIDE(__rodata_end = .);
	} > FLASH_OR_SRAM

	.data :
	{
		PROVIDE(__data_load = LOADADDR(.data));
		PROVIDE(__data_start = .);
		*(.data*)
		PROVIDE(__data_end = .);
	} > SRAM_AT_FLASH

	.ARM.extab :
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > FLASH_OR_SRAM

	.ARM.exidx :
	{
		PROVIDE(__exidx_start = .);
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
		PROVIDE(__exidx_end = .);
	} > FLASH_OR_SRAM

	.bss.retention (NOLOAD) :
	{
		PROVIDE(__bss_retention_start = .);
		*(.bss.retention*)
		PROVIDE(__bss_retention_end = .);
	} > RETENTION

	.bss (NOLOAD) :
	{
		PROVIDE(__bss_start = .);
		*(.bss*)
		PROVIDE(__bss_end = .);
	} > SRAM

	PROVIDE(end = .);

	.stack (ORIGIN(SRAM) + LENGTH(SRAM) - STACK_SIZE) (NOLOAD) :
	{
		PROVIDE(__stack_limit = .);
		. = . + STACK_SIZE;
		PROVIDE(__stack_top = .);
	} > SRAM
}
