/* Nintendo DS BIOS SWI 0x00 veneer. */
asm void SoftReset_020004b2(void)
{
    swi 0x00
    bx lr
}
