/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-13
 * (c) NXP Semiconductors 2013-2015
 * Generated linker script file for LPC4337
 * Created from generic_c.ld (LPCXpresso v7.6 (2 [Build 326] [2015-02-02] ))
 * By LPCXpresso v7.6.2 [Build 326] [2015-02-02]  on Wed Aug 26 15:59:13 ART 2015
 */

ENTRY(ResetISR)

SECTIONS
{

    .text_Flash2 : ALIGN(4)
    {
       FILL(0xff)
       __core_m0app_START__ = .; /* start of slave image */
         KEEP(*(.core_m0app))
         KEEP(*(.core_m0app.data_*)) KEEP(*(.core_m0app.data))
       __core_m0app_END__ = .; /* end of slave image */
       /*
       ASSERT(!(__core_m0app_START__ == __core_m0app_END__), "No slave code for _core_m0app");
       ASSERT( (ABSOLUTE(__core_m0app_START__) == __vectors_start___core_m0app), "M0APP execute address differs from address provided in source image");
       */

    	*(.text_Flash2*) /* for compatibility with previous releases */
    	*(.text_MFlashB512*) /* for compatibility with previous releases */
    	*(.text.$Flash2*)
    	*(.text.$MFlashB512*)
    	*(.rodata.$Flash2*)
    	*(.rodata.$MFlashB512*)
    } > MFlashB512

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

        /* Code Read Protect data */
        . = 0x000002FC ;
        PROVIDE(__CRP_WORD_START__ = .) ;
        KEEP(*(.crp))
        PROVIDE(__CRP_WORD_END__ = .) ;
        ASSERT(!(__CRP_WORD_START__ == __CRP_WORD_END__), "Linker CRP Enabled, but no CRP_WORD provided within application");
        /* End of Code Read Protect */

    } >MFlashA512

    .text : ALIGN(4)
    {
         *(.text*)
        *(.rodata .rodata.* .constdata .constdata.*)
        . = ALIGN(4);

    } > MFlashA512

    /*
     * for exception handling/unwind - some Newlib functions (in common
     * with C++ and STDC++) use this.
     */
    .ARM.extab : ALIGN(4)
    {
    	*(.ARM.extab* .gnu.linkonce.armextab.*)
    } > MFlashA512
    __exidx_start = .;

    .ARM.exidx : ALIGN(4)
    {
    	*(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > MFlashA512
    __exidx_end = .;

    _etext = .;


	
	/* MAIN DATA SECTION */

    .uninit_RESERVED : ALIGN(4)
    {
        KEEP(*(.bss.$RESERVED*))
        . = ALIGN(4) ;
        _end_uninit_RESERVED = .;
    } > RamLoc40_24


	/* Main DATA section (RamLoc40_24) */
	.data : ALIGN(4)
	{
	   FILL(0xff)
	   _data = . ;
	   *(vtable)
	   *(.ramfunc*)
	   *(.data*)
	   . = ALIGN(4) ;
	   _edata = . ;
	} > RamLoc40_24 AT>MFlashA512

	/* DATA section for RamLoc40_16 */
	.data_RAM6 : ALIGN(4)
    {
       FILL(0xff)
       PROVIDE(__start_data_RAM6 = .) ;
       *(.ramfunc.$RAM6)
       *(.ramfunc.$RamLoc40_16)
    	*(.data.$RAM6*)
    	*(.data.$RamLoc40_16*)
       . = ALIGN(4) ;
       PROVIDE(__end_data_RAM6 = .) ;
    } > RamLoc40_16 AT>MFlashA512

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
    } > RamAHB32 AT>MFlashA512
		
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
    } > RamAHB_8M4 AT>MFlashA512

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
    } > RamAHB_8M0 AT>MFlashA512
	
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
    } > RamAHB_ETB16 AT>MFlashA512
    	
   
   /* MAIN BSS SECTION */
    .bss : ALIGN(4)
    {
        _bss = .;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4) ;
        _ebss = .;
        PROVIDE(end = .);
    } > RamLoc40_24
    
	/* BSS section for RamLoc40_16 */
	.bss_RAM6 : ALIGN(4)
    {
       PROVIDE(__start_bss_RAM6 = .) ;
    	*(.bss.$RAM6*)
    	*(.bss.$RamLoc40_16*)
       . = ALIGN(4) ;
       PROVIDE(__end_bss_RAM6 = .) ;
    } > RamLoc40_16
	
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
    } > RamLoc40_24
	
/* NOINIT section for RamLoc40_16 */
	.noinit_RAM6 (NOLOAD) : ALIGN(4)
    {
    	*(.noinit.$RAM6*)
    	*(.noinit.$RamLoc40_16*)
       . = ALIGN(4) ;
    } > RamLoc40_16
	
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
	
/* Genero la seccion para el stack M4 */
    .StackM4 (NOLOAD):
    { 
    	*(.StackM4)    
    } > RamLoc40_16
	
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
    /* le sacamos 32 bytes de offset al stack por las rutinas IAP */
    PROVIDE(_vStackTop = DEFINED(__user_stack_top) ? __user_stack_top : __top_RamLoc40_24 - 32);
    PROVIDE(__valid_user_code_checksum = 0 -
         (_vStackTop
         + (ResetISR + 1)
         + (NMI_Handler + 1)
         + (HardFault_Handler + 1)
         + (( DEFINED(MemManage_Handler) ? MemManage_Handler : 0 ) + 1)   /* MemManage_Handler may not be defined */
         + (( DEFINED(BusFault_Handler) ? BusFault_Handler : 0 ) + 1)     /* BusFault_Handler may not be defined */
         + (( DEFINED(UsageFault_Handler) ? UsageFault_Handler : 0 ) + 1) /* UsageFault_Handler may not be defined */
         ) );
}
