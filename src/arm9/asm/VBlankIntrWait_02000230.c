/* Nintendo DS BIOS SWI 0x05 veneer. */
asm void VBlankIntrWait_02000230(void)
{
    mov r2, #0
    swi 0x05
    bx lr
}
