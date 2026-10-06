/* Nintendo DS BIOS SWI 0x13 veneer. */
asm void HuffUnCompReadByCallback_020003d0(void)
{
    swi 0x13
    bx lr
}
