/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-13
 * (c) NXP Semiconductors 2013-2015
 * Generated linker script file for LPC4337-M0
 * Created from generic_c.ld (LPCXpresso v7.6 (2 [Build 326] [2015-02-02] ))
 * By LPCXpresso v7.6.2 [Build 326] [2015-02-02]  on Wed Aug 26 15:59:13 ART 2015
 */

ENTRY(ResetISR)

SECTIONS
{

    /* MAIN TEXT SECTION */
    .text : ALIGN(4)
    {
        FILL(0xff)
        __vectors_start__ = ABSOLUTE(.) ;
        KEEP(*(.isr_vector))

     	/* Global Section Table */
        . = ALIGN(4) ;
        __section_table_start = .;
        __data_section_table = .;
        LONG(LOADADDR(.data));
        LONG(    ADDR(.data));
        LONG(  SIZEOF(.data));
		LONG(LOADADDR(.data_RAM2));
        LONG(    ADDR(.data_RAM2));
        LONG(  SIZEOF(.data_RAM2));
        LONG(LOADADDR(.data_RAM3));
        LONG(    ADDR(.data_RAM3));
        LONG(  SIZEOF(.data_RAM3));
		LONG(LOADADDR(.data_RAM4));
        LONG(    ADDR(.data_RAM4));
        LONG(  SIZEOF(.data_RAM4));
		LONG(LOADADDR(.data_RAM5));
        LONG(    ADDR(.data_RAM5));
        LONG(  SIZEOF(.data_RAM5));
		LONG(LOADADDR(.data_RAM6));
        LONG(    ADDR(.data_RAM6));
        LONG(  SIZEOF(.data_RAM6));
        __data_section_table_end = .;
        __bss_section_table = .;
        LONG(    ADDR(.bss));
        LONG(  SIZEOF(.bss));
		LONG(    ADDR(.bss_RAM2));
        LONG(  SIZEOF(.bss_RAM2));
        LONG(    ADDR(.bss_RAM3));
        LONG(  SIZEOF(.bss_RAM3));
		LONG(    ADDR(.bss_RAM4));
        LONG(  SIZEOF(.bss_RAM4));
        LONG(    ADDR(.bss_RAM5));
        LONG(  SIZEOF(.bss_RAM5));
		LONG(    ADDR(.bss_RAM6));
        LONG(  SIZEOF(.bss_RAM6));
		__bss_section_table_end = .;
        __section_table_end = . ;
        /* End of Global Section Table */

        *(.after_vectors*)

    } >MFlashB512

    .text : ALIGN(4)
    {
         *(.text*)
        *(.rodata .rodata.* .constdata .constdata.*)
        . = ALIGN(4);

    } > MFlashB512

    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(4)
    {
    	*(.ARM.extab* .gnu.linkonce.armextab.*)
    } > MFlashB512
    __exidx_start = .;

    .ARM.exidx : ALIGN(4)
    {
    	*(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > MFlashB512
    __exidx_end = .;

    _etext = .;


	
	
	/* MAIN DATA SECTION */
	
	.uninit_RESERVED : ALIGN(4)
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > RamLoc32_16A


	/* Main DATA section (RamLoc32_16A) */
	.data : ALIGN(4)
	{
	   FILL(0xff)
	   _data = . ;
	   *(vtable)
	   *(.ramfunc*)
	   *(.data*)
	   . = ALIGN(4) ;
	   _edata = . ;
	} > RamLoc32_16A AT>MFlashB512

 /* DATA section for RamLoc32_16B */
	.data_RAM6 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM6 = .) ;
       *(.ramfunc.$RAM6)
       *(.ramfunc.$RamLoc32_16B)
    	*(.data.$RAM6*)
    	*(.data.$RamLoc32_16B*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM6 = .) ;
    } > RamLoc32_16B AT>MFlashB512
	
    /* DATA section for RamAHB32 */
	.data_RAM2 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM2 = .) ;
       *(.ramfunc.$RAM2)
       *(.ramfunc.$RamAHB32)
    	*(.data.$RAM2*)
    	*(.data.$RamAHB32*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM2 = .) ;
    } > RamAHB32 AT>MFlashB512
		
	/* DATA section for RamAHB_8M4 */
    .data_RAM3 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM3 = .) ;
       *(.ramfunc.$RAM3)
       *(.ramfunc.$RamAHB_8M4)
    	*(.data.$RAM3*)
    	*(.data.$RamAHB_8M4*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM3 = .) ;
    } > RamAHB_8M4 AT>MFlashB512

	/* DATA section for RamAHB_8M0 */
    .data_RAM4 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM4 = .) ;
       *(.ramfunc.$RAM4)
       *(.ramfunc.$RamAHB_8M0)
    	*(.data.$RAM4*)
    	*(.data.$RamAHB_8M0*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM4 = .) ;
    } > RamAHB_8M0 AT>MFlashB512
	
	/* DATA section for RamAHB_ETB16 */
    .data_RAM5 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM5 = .) ;
       *(.ramfunc.$RAM5)
       *(.ramfunc.$RamAHB_ETB16)
    	*(.data.$RAM5*)
    	*(.data.$RamAHB_ETB16*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM5 = .) ;
    } > RamAHB_ETB16 AT>MFlashB512

   
   
   /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
    } > RamLoc32_16A
	
	/* BSS section for RamLoc32_16B */
	.bss_RAM6 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM6 = .) ;
    	*(.bss.$RAM6*)
    	*(.bss.$RamLoc32_16B*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM6 = .) ;
    } > RamLoc32_16B
    
	/* BSS section for RamAHB32 */
	.bss_RAM2 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM2 = .) ;
    	*(.bss.$RAM2*)
    	*(.bss.$RamAHB32*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM2 = .) ;
    } > RamAHB32
		
	/* BSS section for RamAHB_8M4 */
    .bss_RAM3 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM3 = .) ;
    	*(.bss.$RAM3*)
    	*(.bss.$RamAHB_8M4*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM3 = .) ;
    } > RamAHB_8M4
	
	/* BSS section for RamAHB_8M0 */
    .bss_RAM4 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM4 = .) ;
    	*(.bss.$RAM4*)
    	*(.bss.$RamAHB_8M0*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM4 = .) ;
    } > RamAHB_8M0
	
	/* BSS section for RamAHB_ETB16 */
    .bss_RAM5 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM5 = .) ;
    	*(.bss.$RAM5*)
    	*(.bss.$RamAHB_ETB16*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM5 = .) ;
    } > RamAHB_ETB16

	
  
/* DEFAULT NOINIT SECTION */
    .noinit (NOLOAD): ALIGN(4)
    {
        _noinit = .;
        *(.noinit*)
         . = ALIGN(4) ;
        _end_noinit = .;
    } > RamLoc32_16A	
	
/* NOINIT section for RamLoc32_16B */
	.noinit_RAM6 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM6*)
    	*(.noinit.$RamLoc32_16B*)
       . = ALIGN(4) ;
    } > RamLoc32_16B
 
 /* NOINIT section for RamAHB32 */
	.noinit_RAM2 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM2*)
    	*(.noinit.$RamAHB32*)
       . = ALIGN(4) ;
    } > RamAHB32

 /* NOINIT section for RamAHB_8M4 */
	.noinit_RAM3 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM3*)
    	*(.noinit.$RamAHB_8M4*)
       . = ALIGN(4) ;
    } > RamAHB_8M4
	
 /* NOINIT section for RamAHB_8M0 */
	.noinit_RAM4 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM4*)
    	*(.noinit.$RamAHB_8M0*)
       . = ALIGN(4) ;
    } > RamAHB_8M0
	
	/* NOINIT section for RamAHB_ETB16 */
	.noinit_RAM5 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM5*)
    	*(.noinit.$RamAHB_ETB16*)
       . = ALIGN(4) ;
    } > RamAHB_ETB16
	
/* Genero la seccion para el stack M0 */
    .StackM0 (NOLOAD):
    { 
    	*(.StackM0)    
    } > RamLoc32_16B
	
/* Genero la seccion para memoria compartida */
    .Queues32 (NOLOAD):
    { 
    	*(.Queues32)    
    } > RamAHB32

/* Genero seccion IPC M4 -> M0 */
    .ipcM4 (NOLOAD):
    { 
    	*(.ipcM4)    
    } > RamAHB_8M4
	
/* Genero seccion IPC M0 -> M4 */
    .ipcM0 (NOLOAD):
    { 
    	*(.ipcM0)    
    } > RamAHB_8M0
	
/* Genero seccion RamAHB_ETB16 */
    .AHB_ETB16 (NOLOAD):
    { 
    	*(.AHB_ETB16)    
    } > RamAHB_ETB16

	
    PROVIDE(_pvHeapStart = DEFINED(__user_heap_base) ? __user_heap_base : .);
    PROVIDE(_vStackTop = DEFINED(__user_stack_top) ? __user_stack_top : __top_RamLoc32_16A - 0);
    PROVIDE(__valid_user_code_checksum = 0 -
         (_vStackTop
         + (ResetISR + 1)
         + (NMI_Handler + 1)
         + (HardFault_Handler + 1)
         ) );
}  
