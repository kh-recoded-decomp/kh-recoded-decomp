/* Nintendo DS BIOS SWI 0x03 veneer. */
asm void WaitByLoop_020006c6(void)
{
    swi 0x03
    bx lr
}
