/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2015
 * (c) NXP Semiconductors 2013-2015
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v7.6.2 [Build 326] [2015-02-02]  on Wed Aug 26 15:59:13 ART 2015)
*/

MEMORY
{
  /* Define each memory region */
  /* MFlashA512 (rx) : ORIGIN = 0x1a000000, LENGTH = 0x80000 */ /* 512K bytes -- M4 */
  MFlashB512 (rx) : ORIGIN = 0x1b000000, LENGTH = 0x80000 /* 512K bytes -- M0 */

  /* RamLoc32 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x8000 */ /* 32K bytes -- M0 */
  RamLoc32_16A (rwx) : ORIGIN = 0x10000000, LENGTH = 0x4000 /* 16K bytes -- M0 */
  RamLoc32_16B (rwx) : ORIGIN = 0x10004000, LENGTH = 0x4000 /* 16K bytes -- M0 -- Stack region for RTOS */
  /* RamLoc40 (rwx) : ORIGIN = 0x10080000, LENGTH = 0xa000 */ /* 40K bytes -- M4 */
  
  RamAHB32 (rwx) : ORIGIN = 0x20000000, LENGTH = 0x8000 /* 32K bytes -- shared region -- queue region in our current application*/
  
  /* RamAHB16 (rwx) : ORIGIN = 0x20008000, LENGTH = 0x4000 */ /* 16K bytes */
  RamAHB_8M4 (rwx) : ORIGIN = 0x20008000, LENGTH = 0x2000 /* 8K bytes IPC queue M4 -> M0 */
  RamAHB_8M0  (rwx) : ORIGIN = 0x2000a000, LENGTH = 0x2000 /* 8K bytes IPC queue M0 -> M4 */	
  
  RamAHB_ETB16 (rwx) : ORIGIN = 0x2000c000, LENGTH = 0x4000 /* 16K bytes -- shared */

}
  /* Define a symbol for the top of each memory region */
  /* __top_MFlashA512 = 0x1a000000 + 0x80000; */
  __top_MFlashB512 = 0x1b000000 + 0x80000;
  
  /* __top_RamLoc32 = 0x10000000 + 0x8000; */
  __top_RamLoc32_16A = 0x10000000 + 0x4000;
  __top_RamLoc32_16B = 0x10004000 + 0x4000;
  
  /* __top_RamLoc40 = 0x10080000 + 0xa000; */
										  
   __top_RamAHB32 = 0x20000000 + 0x8000;
  
  /* __top_RamAHB16 = 0x20008000 + 0x4000; */
  __top_RamAHB8M4 = 0x20008000 + 0x2000;
  __top_RamAHB8M0 = 0x2000a000 + 0x2000;
  
  __top_RamAHB_ETB16 = 0x2000c000 + 0x4000;