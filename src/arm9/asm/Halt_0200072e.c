/* Nintendo DS BIOS SWI 0x06 veneer. */
asm void Halt_0200072e(void)
{
    swi 0x06
    bx lr
}
